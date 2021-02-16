/* please delete this line */


#include <graphics_lib1.h>
#include <stdio.h>
#include <conio.h>

int main(void)
{
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT ev;
    int done = 0, overpaint = 0, outlined = 0;
    int hide_mouse_cursor;
    int old_x_pos, old_y_pos;
    int new_x_pos, new_y_pos;
    int num_buttons;
    int num_clicks = 0;


	initwindow(640, 480);

    setbkcolor(BLACK);
    setcolor(BLUE);

	al_install_mouse();

    num_buttons = al_get_mouse_num_buttons();
    printf("\nnum mouse buttons is %d\n", num_buttons);

    /* create an event queue */
    event_queue = al_create_event_queue();

    /* register display and mouse as event sources */
    al_register_event_source(event_queue, al_get_display_event_source(DISPLAY));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    printf("\nDo you want to hide the mouse cursor? (0 = NO, 1 = YES) ");
    scanf("%d", &hide_mouse_cursor);

    if (hide_mouse_cursor)
        al_hide_mouse_cursor(DISPLAY);

    initfont();

    new_x_pos = 320;
    new_y_pos = 240;

    outtextxy(5,5,"Press left mouse button to quit");

	while (!done)
	{
	    //old_x_pos = new_x_pos;
	    //old_y_pos = new_y_pos;

        /*
        if (outlined)
            circle(new_x_pos, new_y_pos, 10, 2);
        else
            filled_circle(new_x_pos, new_y_pos, 10 ,BLUE);
        */

	    /* check if there have been events */
	    al_wait_for_event(event_queue, &ev);

	    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	    {
	        done = 1;
	    }
	    else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
	    {
	        new_x_pos = ev.mouse.x;
	        new_y_pos = ev.mouse.y;
	    }
	    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
	    {
	        if (ev.mouse.button & 1) /* if left mouse button down */
	        {
	            done = 1;
	            printf("\n left mouse button down");
	        }

            if (ev.mouse.button & 2) /* right mouse button down */
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
            circle(new_x_pos, new_y_pos, 10, 2);
        }
        else
            filled_circle(new_x_pos, new_y_pos, 10 ,BLUE);


        update_display();

        if (overpaint)
        {
            //al_flip_display();
            //al_clear_to_color(al_map_rgb(0,0,0));
            //filled_circle(old_x_pos, old_y_pos, 10 ,BLACK);
            //if (outlined)
            //{
            //    setcolor(BLACK);
            //    circle(new_x_pos, new_y_pos, 10, 2);
            //}
            //else
                filled_circle(new_x_pos, new_y_pos, 10 ,BLACK);
            //cleardevice();
        }

	}

	/* Wait for a key press */
	printf("\nPress a key to quit");
    getch();

    al_uninstall_mouse();
    /* remove the display */
    closegraph();


    return 0;
}
