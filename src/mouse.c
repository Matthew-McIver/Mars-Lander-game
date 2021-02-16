#include <graphics_lib.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{

    int done = 0, overpaint = 0, outlined = 0;
    int hide_cursor;
    int x_pos, y_pos;
    int num_clicks = 0;


	initwindow(640, 480);

    setbkcolor(BLACK);
    setcolor(BLUE);

    /* initialize the mouse */
	initmouse();

    /* create an event queue */
    create_event_queue();

    /* register display and mouse as event sources */
    reg_display_events();
    reg_mouse_events();

    printf("\nDo you want to hide the mouse cursor? (0 = NO, 1 = YES) ");
    scanf("%d", &hide_cursor);

    if (hide_cursor)
        hide_mouse_cursor();

    initfont();

    x_pos = 320;
    y_pos = 240;

    outtextxy(5,5,"Press left mouse button to quit");

	while (!done)
	{
	    /* wait for event  */
	    wait_for_event();

        /* if graphics windows closed then exit loop */
	    if (event_close_display() )
	        done = 1;
	    else if (event_mouse_position_changed() ) /* mouse moved */
	    {
	        get_mouse_coordinates();
	        x_pos = XMOUSE;
	        y_pos = YMOUSE;
	    }

	    else if (event_mouse_button_down())
	    {
	        if (event_mouse_left_button_down()) /* if left mouse button down */
	            done = 1;

            if (event_mouse_right_button_down()) /* if right mouse button down */
               num_clicks++;
	    }
	    num_clicks = num_clicks % 4;

	    if (num_clicks == 0)
	    {
	        overpaint = 0;
	        outlined = 0;
	    }
	    else if (num_clicks == 1)
	    {
	        overpaint = 0;
	        outlined = 1;
	    }
	    else if (num_clicks == 2)
	    {
	        overpaint = 1;
	        outlined = 0;
	    }
	    else if (num_clicks == 3)
	    {
	        overpaint = 1;
	        outlined = 1;
	    }

        if (outlined)
        {
            setcolor(BLUE);
            circle(x_pos, y_pos, 10, 2);
        }
        else
            filled_circle(x_pos, y_pos, 10 ,BLUE);


        update_display();

        if (overpaint)
        {
            filled_circle(x_pos, y_pos, 10 ,BLACK);
        }

	}

	/* Wait for a key press */
	printf("\nPress a key to quit");
    getch();

    /* close the mouse */
    closemouse();

    /* remove the display */
    closegraph();


    return 0;
}
