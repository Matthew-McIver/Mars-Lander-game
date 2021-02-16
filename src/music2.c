/*
 *	A program to demonstrate a simple chromatic scale
 *	C Programming laboratory 3
 */

#include <midi_lib.h>

int main(void)
{
	/* Declare integer variables for specifying a note */
	int pitch, channel, velocity, offset;

	/* Set the pitch variable to 60, which is middle C */
	pitch = 60;

	/* We will play the note on MIDI channel 1 */
	channel = 1;

	/* The note will have a medium velocity (volume) */
	velocity = 64;

    /* initialize the midi functions */
    midi_start();

	/* Play an octave's worth of chromatic scale */
	for (offset = 0; offset <= 12; offset++)
	{
		/* Start playing a note */
		midi_note(pitch + offset, channel, velocity);

		/* Wait, so that we can hear the note playing */
		pause(400);

		/* Turn the note off */
		midi_note(pitch + offset, channel, 0);
	}

    /* close down all midi functions */
    midi_close();

	return 0;
}
