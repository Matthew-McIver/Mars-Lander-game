
#include <graphics_lib.h>

int main(void)
{
    /* Declare two variables for the x and y positions */
    int x_position, y_position;

	/* Open a graphics window */
	/* Make it 640 pixels wide by 480 pixels high */
	initwindow(1280, 960);

	/* Set up some coordinates */
	x_position = 100;
	y_position = 340;

    /* choose red pen colour */
	setcolor(RED);

    /* draw a circle on the screen buffer
     at x_position, y_position
     with radius 10 and line thickness 2 */
    circle(x_position, y_position, 10, 2);

    /* move the contents of the screen buffer to the display */
    update_display();

	/* Wait for a key press */
    getch();

    /* remove the display */
    closegraph();


    return 0;
}
