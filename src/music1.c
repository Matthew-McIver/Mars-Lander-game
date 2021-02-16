/*
 *	A program to demonstrate simple musical operations
 *	C Programming laboratory 1
 */

/*  This line allows the compiler to understand the
 *	midi functions
 */
#include <amio_lib.h>

/*
 * The main function - the program starts executing here
 */
int main(void)
{
	/* Declare integer variables for specifying a note */
	int pitch, channel, velocity;

    /* initialize the midi functions */
    midi_start();

	/* Set the pitch variable to 60, which is middle C */
	pitch = 60;

	/* We will play the note on MIDI channel 1 */
	channel = 1;

	/* The note will have a medium velocity (volume) */
	velocity = 64;

	/* Start playing a middle C at moderate volume */
	midi_note(pitch, channel, velocity);

	/* Wait, for 1 second, so that we can hear the note playing */
	pause(1000);

	/* Turn the note off by setting its volume to 0 */
	midi_note(pitch, channel, 0);

    /* close down all midi functions */
    midi_close();

	return 0;
}
