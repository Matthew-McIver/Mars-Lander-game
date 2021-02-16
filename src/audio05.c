//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API - Tremolo effect example
//  File:   ex_05.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//  This example demonstrates a simple tremolo effect. It creates a sinusoid
//  that modulates the gain of the input signal, storing the results to the
//  output signal.
//
//=============================================================================
//  Copyright and License Information
//=============================================================================
//  Copyright (c) 2013 Dimitri Zantalis <dz548@york.ac.uk>
//
//  For license information see 'include/license.h'
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

#ifndef M_PI
#define M_PI  (3.14159265)
#endif

#define kInputSignalLocation "samples/vocals.wav"
#define kOutputSignalLocation "samples/vocals_out_05.wav"

int main()
{
    //=============================================================================
    //STEP 1 - INITIALISATION
    //=============================================================================
    SIGNAL input,output,LFO;
    int i=0;
    int j=0;
    float rateHz=10.0f;

    //Initialise SIGNAL structures.
    memset(&input,0,sizeof(SIGNAL));
    memset(&output,0,sizeof(SIGNAL));

    //=============================================================================
    //STEP 2 - OPEN AUDIO FILE AND READ INTO MEMORY
    //=============================================================================
    //Read input signal into memory.
    printf("Reading %s into memory...\n",kInputSignalLocation);
    wavread(kInputSignalLocation, &input);

    //=============================================================================
    //STEP 3 - PREPARE THE OUTPUT & LFO SIGNALS
    //=============================================================================
    //Set up output SIGNAL structure.
    Fill_SIGNAL(&output,
                input.frames,
                input.samplerate,
                input.channels,
                SF_FORMAT_WAV|SF_FORMAT_PCM_32,
                input.sections,
                input.seekable,
                NULL);

    //Allocate space for the 'output.data' buffer.
    output.data=(float *)malloc(sizeof(float)* input.frames*input.channels);

    //Although we are not going to save the LFO signal, we use a SIGNAL structure here
    //just to keep consistent with the audio_lib API. A simple array would do, but
    //the SIGNAL structure already provides us with an appropriate field (data) so we
    //are going to use this.
        Fill_SIGNAL(&LFO,
                input.frames,
                input.samplerate,
                input.channels,
                SF_FORMAT_WAV|SF_FORMAT_PCM_32,
                input.sections,
                input.seekable,
                NULL);

    //Allocate space for the 'LFO.data' buffer. Note that LFO.data will contain
    //the samples of a mono signal (we use only frames to calculate the size of
    //the required memory space).
    LFO.data=(float *)malloc(sizeof(float)* input.frames);

    //Create a sinusoid with period rateHz and scale it from 0.0f to 1.0f (instead of
    //-1.0f to 1.0f which is the output of the sin function)
    for(i=0; i<input.frames; i++)
    {
        LFO.data[i]=0.5f*(sin(2.0f*M_PI*i*(rateHz/LFO.samplerate))+1.0f);
    }

    //=============================================================================
    //STEP 4 - PROCESSING
    //=============================================================================
    //In this example we create a tremolo effect. The amplitude of the input
    //is modulated (multiplied) with our LFO signal.

    for(i=0; i<input.frames; i++)
    {
        for(j=0; j<input.channels; j++)
        {
            //Note that all channels(if more than one) are multiplied
            //by the same LFO value. An interesting effect could be created
            //by multiplying each channel with a different LFO.
            output.data[i+j]=input.data[i+j]*LFO.data[i];
        }
    }

    //=============================================================================
    //STEP 5 - WRITE OUTPUT TO AUDIO FILE
    //=============================================================================
    //Write output file to disk
    printf("\n\nWriting audio to output file %s\n",kOutputSignalLocation);
    wavwrite(kOutputSignalLocation, &output);

    //=============================================================================
    //STEP 6 - CLEAN UP
    //=============================================================================
    free(input.data);
    free(output.data);
    free(LFO.data);

    return 0;
}


