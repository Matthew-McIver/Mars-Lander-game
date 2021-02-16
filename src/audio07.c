//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API
//  File:   ex_fileplayback.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//
//
//=============================================================================
//  Copyright and License Information
//=============================================================================
//  Copyright (c) 2013 Dimitri Zantalis <dz548@york.ac.uk>
//
//  For license information see 'include\license.h'
//
//=============================================================================
//	Recommended Reading List & References
//=============================================================================
//  [1] libsndfile, C library for reading/writing audio files,
//      http://www.mega-nerd.com
//
//  [2] PortAudio, 'Portable Cross-platform Audio I/O, http://www.portaudio.com
//
//  [3] PortMidi, 'Portable MIDI I/O library', http://portmedia.sourceforge.net/portmidi

#include "amio_lib.h"
#include "conio.h"

#define VOLUME_INCREMENT (0.1f)
#define PAN_INCREMENT (0.1f)

typedef struct
{
    SIGNAL drums;
    long int ridx;
    float volume;
    float pan;
    char message[20];
}
USERDATA;

//-----------------------------------------------------------------------------
// This routine will be called by the PortAudio engine when audio is needed.
// It may called at interrupt level on some machines so don't do anything
// that could mess up the system like calling malloc() or free().
//-----------------------------------------------------------------------------
static int processingCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
    USERDATA *data = (USERDATA*)userData;
    float *out = (float*)outputBuffer;
    unsigned long i;
    float aL,aR;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer;


    for( i=0; i<framesPerBuffer; i++ )
    {
        //Apply panning and volume
        aL=(1.0f-data->pan)*data->volume;
        aR=(1.0f-aL)*data->volume;

        *out++ = aL*data->drums.data[data->ridx];  /* left */
        *out++ = aR*data->drums.data[data->ridx];  /* right */

        data->ridx++;
        if(data->ridx>=data->drums.frames) data->ridx=0;
    }

    return paContinue;
}

//-----------------------------------------------------------------------------
//This routine is called by portaudio when playback is done.
//-----------------------------------------------------------------------------
static void audioStreamFinished( void* userData )
{
    USERDATA *data = (USERDATA *) userData;
    printf( "Stream Completed: %s\n", data->message );
}

int main(void);
int main(void)
{
    //=============================================================================
    //Variables and Data Structures
    //=============================================================================
    PaError err=0;
    char key;
    char ctrl;
    USERDATA data;
    AUDIOSTREAM outStream;

    //=============================================================================
    //STEP 0 - Preliminary set-up and initialisation
    //=============================================================================

    //Set up AUDIOSTREM structure.
    outStream.stream=NULL;
    outStream.sampleRate=44100;
    outStream.sampleFormat=paFloat32;
    outStream.inChannels=0;
    outStream.outChannels=2;
    outStream.framesPerBuffer=512;

    //Read audio file into memory (i.e into 'data.drums' SIGNAL structure).
    err=wavread("samples/drums.wav",&data.drums);
    checkErr(err,kSndFileSystem,"Failed to read file into memory.");

    //Set read index 'ridx' to zero.
    data.ridx=0;
    data.volume=0.3;
    data.pan=0.5;

    //=============================================================================
    //STEP 1 - Initialise audio system
    //=============================================================================
    err=initialiseAudioSystem();
    err=checkErr(err,kAudioSystem,"Failed to initialise audio system.");
    if(err!=0)
    {
        printf("Application will exit.");
        exit(EXIT_FAILURE);
    }

    //=============================================================================
    //STEP 2 - Open an audio stream
    //=============================================================================
    err=openDefaultAudioStream(&outStream,processingCallback,&data);
    checkErr(err,kAudioSystem,"Failed to open default audio stream.");

    //Register 'audioStreamFinished' callback with our stream.
    //This callback will be called as sson as the audio stream is stopped.
    err=setAudioStreamFinishedCallback(&outStream,&audioStreamFinished);

    //=============================================================================
    //STEP 3 - Main control loop
    //=============================================================================
    do
    {
        printf("enter command >> ");
        scanf("%c",&key);
        //printf("ASCII of %c: %d\n",key,(int)key);

        switch((int)key)
        {
        case 97:
            printf("Audio stream playing...\n\n");
            err=startAudioStream(&outStream);
            checkErr(err,kAudioSystem,"Failed to start audio stream.");
            do{
                printf("Volume: %1.1f | Pan: %1.1f\r",data.volume,data.pan);
                ctrl=getch();
                switch(ctrl){
                    case 72:
                    data.volume=data.volume+VOLUME_INCREMENT;
                    if(data.volume>1.0f) data.volume=1.0f;
                    break;
                    case 80:
                    data.volume=data.volume-VOLUME_INCREMENT;
                    if(data.volume<0.0f) data.volume=0.0f;
                    break;
                    case 75:
                    data.pan=data.pan-PAN_INCREMENT;
                    if(data.pan<0.0f) data.pan=0.0;
                    break;
                    case 77:
                    data.pan=data.pan+PAN_INCREMENT;
                    if(data.pan>1.0f) data.pan=1.0f;
                    break;
                }
            }while(ctrl!=115);
            printf("\n");
            //break;
        case 115:
            printf("Audio stream stopped.\n");
            err=stopAudioStream(&outStream);
            checkErr(err,kAudioSystem,"Failed to stop audio stream.");
            break;
        default:
            break;
        }
        fflush(stdin);
    }
    while (key != 'q');

    err=closeAudioStream(&outStream);
    checkErr(err,kAudioSystem,"Failed to close audio stream.");

    //=============================================================================
    //PART 4 - Clean up
    //=============================================================================
    err=terminateAudioSystem();
    checkErr(err,kAudioSystem,"Failed to terminate audio system.");

    return err;
}
