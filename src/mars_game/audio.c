#include "amio_lib.h"
#include "conio.h"

#include "audio.h"

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

static void audioStreamFinished( void* userData )
{
    USERDATA *data = (USERDATA *) userData;
    printf( "Stream Completed: %s\n", data->message );
}

USERDATA data;
AUDIOSTREAM outStream;

void initAudio() {
    PaError err=0;

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

}

void readAudioLoop(char* file) {
    PaError err=0;
    err=wavread(file,&data.drums);
    checkErr(err,kSndFileSystem,"Failed to read file into memory.");
}

void startAudioLoop() {
    PaError err=0;
    printf("Audio stream playing...\n\n");
    err=startAudioStream(&outStream);
    checkErr(err,kAudioSystem,"Failed to start audio stream.");
}

void endAudioLoop() {
    PaError err=0;
    printf("Audio stream stopped.\n");
    err=stopAudioStream(&outStream);
    checkErr(err,kAudioSystem,"Failed to stop audio stream.");
}
