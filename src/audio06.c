//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API
//  File:   ex_06.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//  Play a sine through the speakers for five seconds
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

#define kDrumsSignal "samples/drums.wav"
#define kVocalsSignal "samples/vocals.wav"

#define NUM_SECONDS   (5)
#define TABLE_SIZE (256)

typedef struct
{
    float sine[TABLE_SIZE];
    int left_phase;
    int right_phase;
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

    (void) timeInfo; // Prevent unused variable warnings.
    (void) statusFlags;
    (void) inputBuffer;

    for( i=0; i<framesPerBuffer; i++ )
    {
        *out++ = 0.3*data->sine[data->left_phase];  // left
        *out++ = 0.3*data->sine[data->right_phase];  // right
        data->left_phase += 1;
        if( data->left_phase >= TABLE_SIZE ) data->left_phase -= TABLE_SIZE;
        data->right_phase += 3; // higher pitch so we can distinguish left and right.
        if( data->right_phase >= TABLE_SIZE ) data->right_phase -= TABLE_SIZE;
    }

    return paContinue;
}

//-----------------------------------------------------------------------------
//This routine is called by portaudio when playback is done.
//-----------------------------------------------------------------------------
static void StreamFinished( void* userData )
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
    USERDATA data;
    AUDIOSTREAM outStream;
    int i;

    //=============================================================================
    //STEP 0 - Preliminary set-up and initialisation
    //=============================================================================

    //Initialise sinusoidal wavetable
    for( i=0; i<TABLE_SIZE; i++ )
    {
        data.sine[i] = (float) sin( ((double)i/(double)TABLE_SIZE) * M_PI * 2. );
    }
    data.left_phase = data.right_phase = 0;

    //Initialise message of data structure
    sprintf( data.message, "No Message" );

    //Set up AUDIOSTREAM structure
    outStream.stream=NULL; //Will get a value after openDefaultAudioStream call
    outStream.sampleRate=44100;//The stream sample rate
    outStream.sampleFormat=paFloat32;//The stream sample format (float 32-bit in this case)
    outStream.inChannels=0;//Zero input channels indicates that we need an output only stream
    outStream.outChannels=2;//Two-channels for stereo output
    outStream.framesPerBuffer=512;//Number of frames of the buffers in the processing callback function

    //=============================================================================
    //STEP 1 - Initialise audio system.
    //=============================================================================
    initialiseAudioSystem();

    //=============================================================================
    //STEP 2 - Open an audio stream
    //=============================================================================
    openDefaultAudioStream(&outStream,processingCallback,&data);

    //Also register a callback function to be called as soon as
    //the stream stops. Handy to have here although it does not
    //do much in this example.
    setAudioStreamFinishedCallback(&outStream,&StreamFinished);

    //=============================================================================
    //STEP 3 - Main control loop
    //=============================================================================

    //Start the audio stream
    startAudioStream(&outStream);

    //Pause for NUM_SECONDS seconds
    printf("Pause for %i seconds\n",NUM_SECONDS);
    pause(NUM_SECONDS*1000);

    //Stop the audio stream
    stopAudioStream(&outStream);

    //=============================================================================
    //PART4 - Clean up
    //=============================================================================

    //Close the audio stream
    closeAudioStream(&outStream);

    //Terminate the audio system.
    terminateAudioSystem();

    printf("Example completed.\n");

    return 0;
}

