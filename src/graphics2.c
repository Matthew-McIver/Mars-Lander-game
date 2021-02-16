/*
 *	A program to demonstrate plotting a parabola
 *	C Programming laboratory 3
 */

#include <stdio.h>
#include <graphics_lib.h>

int main(void)
{
	/* Declare variables for projectile modelling */
	double pos_x, pos_y, init_pos_x, init_pos_y, vel_x, vel_y;
	double time, gravity;

	/* Initialise the projectile position */
	init_pos_x = 100;
	init_pos_y = 340;

	/* Initialise the projectile velocity */
	vel_x = 60;
	vel_y = 60;

	/* Initialise gravity */
	gravity = 9.81;

	/* Open a graphics window */
	/* Make it 640 pixels wide by 480 pixels high */
	initwindow(1280, 960);

	/* Move to starting position */
	moveto((int)init_pos_x, (int)init_pos_y);

	/* Loop over time */
	for (pos_x = init_pos_x; pos_y <= init_pos_y; pos_x++)
	{
		/* Calculate new height */
		time = (pos_x - init_pos_x) / vel_x;
		pos_y = init_pos_y - (vel_y * time) + (gravity * time * time);

		/* Draw a line */
		lineto((int)pos_x, (int)pos_y, 1);
        update_display();
	}

	/* Wait for a key press */
	getch();

	/* Close the graphics window */
	closegraph();

	return 0;
}
