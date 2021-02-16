//=============================================================================
//  Introduction to C Programming (Audio Programming Exercises)
//=============================================================================
//  audio_lib API - Pass-through example
//  File:   ex_01.c
//  Author: Dimitri Zantalis
//  Date:   September 2013
//
//=============================================================================
//  Discussion
//=============================================================================
//  The following example opens an audio file and saves it
//  with another name. It demonstrates the basic functions
//  needed for such a task. In particular it demonstrates:
//      -How to open an audio file and read it into memory.
//      -How to create a new SIGNAL structure and prepare
//       it for processing.
//      -How to save/write audio data (samples) into disk.
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
#define kOutputSignalLocation "samples/drums_out_01.wav"

int main()
{
    //=============================================================================
    //STEP 1 - INITIALISATION
    //=============================================================================
    int err=0;

    //Create two SIGNAL structures. These structures contain important
    //information about the signals that will be used (input and output).
    SIGNAL input,output;

    //Initialise SIGNAL structures.
    //Set the memory space occupied by the structures to zero.
    //Although this step is not always necessary,
    //it is good programming practice to initialise all variables, structures etc.
    memset(&input,0,sizeof(SIGNAL));
    memset(&output,0,sizeof(SIGNAL));

    //=============================================================================
    //STEP 2 - OPEN AUDIO FILE AND READ INTO MEMORY
    //=============================================================================
    //Read input signal into memory.
    //The input signal is loaded into the memory location
    //pointed by the 'input.data' structure field (which is a pointer to an array of floats).
    printf("Reading '%s' into memory...\n",kInputSignalLocation);
    err=wavread(kInputSignalLocation, &input);
    checkErr(err,kSndFileSystem,"Failed to read audio file into memory");

    //Display information about the input signal.
    printf("\n\n");
    displaySndInfo(&input);

    //=============================================================================
    //STEP 3 - PREPARE THE OUTPUT SIGNAL
    //=============================================================================
    //Set up output SIGNAL structure. We want to write the output signal
    //to a file so we need to set up the SIGNAL structure with
    //the file format, sampling rate and some other
    //parameters of the output file that we want. In this case we only want to
    //copy the input to the output so we set up the output SIGNAL structure
    //with the same state as the input SIGNAL structure.
    Fill_SIGNAL(&output,
                input.frames,
                input.samplerate,
                input.channels,
                SF_FORMAT_WAV|SF_FORMAT_PCM_32,
                input.sections,
                input.seekable,
                NULL);

    //=============================================================================
    //STEP 4 - PROCESSING
    //=============================================================================
    //This is where signal processing takes place. In our case
    //we want to copy the input into the output, unmodified.
    //The only thing we have to do is to assign the data field of the input SIGNAL
    //to the data field of the output SIGNAL
    output.data=input.data; //Please note this is a pointer assignment

    //=============================================================================
    //STEP 5 - WRITE OUTPUT TO AUDIO FILE
    //=============================================================================
    //Write output file to disk
    printf("\n\nWriting audio to output file %s\n",kOutputSignalLocation);
    err=wavwrite(kOutputSignalLocation, &output);
    checkErr(err,kSndFileSystem,"Failed to write audio file to disk");

    //=============================================================================
    //STEP 6 - CLEAN UP
    //=============================================================================
    //We have now fnished with our files, but before we exit we need
    //to clean up any memory we used. We use the function 'free' for this task.
    free(input.data);
    //free(output.data); No need to free output.data because this point to
    //input.data which at this point is already deleted. Trying to delete
    //output.data will result in a crash.

    return 0;
}


