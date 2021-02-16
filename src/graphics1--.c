/*
 *	A program to demonstrate simple graphical operations
 *	C Programming laboratory 1
 */

/*  This line allows the compiler to understand the
 *	graphics functions
 */
#include <graphics_lib.h>
#include <stdio.h>

/*
 * The main function - the program starts executing here
 */
int main(void)
{
	/* Declare two variables for the x and y positions */
	int x_position, y_position;

	/* Open a graphics window */
	/* Make it 640 pixels wide by 480 pixels high */
	initwindow(640, 480);

	/* Set up some coordinates */
	x_position = 100;
	y_position = 320;

    /* Set the current drawing colour to be red */
	setcolor(RED);

	/********  DRAW STICK MAN *************/
	/* Draw head */
	circle(x_position, y_position,  20, 2);
	    update_display();

	/* Wait for a key press */
	getch();

	/* Draw body */
	line(x_position,y_position+20,x_position,y_position+80, 2);
	/* Draw arms */
	line(x_position-20,y_position+40,x_position+20,y_position+40, 2);
	/* draw legs */
	    update_display();

	/* Wait for a key press */
	getch();
	line(x_position-30,y_position+120,x_position,y_position+80, 2);
	line(x_position+30,y_position+120,x_position,y_position+80, 2);
    /********  END OF STICK MAN ***********/

    update_display();

	/* Wait for a key press */
	getch();

	/* Close the graphics window */
	closegraph();

	return 0;
}

