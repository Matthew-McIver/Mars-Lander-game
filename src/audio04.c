//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API - Delay effect example
//  File:   ex_04.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//  This example demonstrates a simple delay effect. It implements the following
//  difference equation: y(n)=x(n)+g*x(n-M) where M is the delay in samples and
//  g is a damping coefficient.
//
//=============================================================================
//  Copyright and License Information
//=============================================================================
//  Copyright (c) 2013 Dimitri Zantalis <dz548@york.ac.uk>
//
//  For license information see 'license.h'
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

#define kInputSignalLocation "samples/drums.wav"
#define kOutputSignalLocation "samples/drums_out_04.wav"

int main()
{
    //=============================================================================
    //STEP 1 - INITIALISATION
    //=============================================================================
    SIGNAL input,output;
    int i=0;
    int j=0;
    int M=8192;
    float g=0.6;

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
    //STEP 3 - PREPARE THE OUTPUT SIGNAL
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

    //=============================================================================
    //STEP 4 - PROCESSING
    //=============================================================================
    //In this example we delay the input signal by M samples
    //and store the results in the output signal
    //We use two nested for loops, one to cover all frames
    // and the other to cover all channels. This way we provide a generic
    //approach to hanndle all channels of a signal. Please note that
    //depending on the processing we do the left and right channels might
    //have to be processed separately. For this exmaple the following code
    //works fine.

    for(i=0;i<input.frames;i++){
        for(j=0;j<input.channels;j++){
            if (i<M) {
                output.data[i+j]=input.data[i+j];
            }
            else{
                output.data[i+j]=input.data[i+j]+g*input.data[i+j-M];
            }
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

    return 0;
}

