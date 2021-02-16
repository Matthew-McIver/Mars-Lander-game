//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API - Reverse signal example
//  File:   ex_03.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//  This example demonstrates how to reverse a signal.
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
#define kOutputSignalLocation "samples/drums_out_03.wav"

int main()
{
    //=============================================================================
    //STEP 1 - INITIALISATION
    //=============================================================================
    //Create input and output SIGNAL structures.
    SIGNAL input,output;
    int i=0;

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
    //In this example we reverse the input signal
    //and store the results in the output signal

    for(i=0;i<input.frames;i++){
        output.data[i]=input.data[input.frames-i];

        //If the signal is stereo then a frame comprises two samples
        if (input.channels==2)
            output.data[i+1]=input.data[input.frames-i+1];
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
