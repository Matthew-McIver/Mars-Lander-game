/* this program demonstrates how multiple
   objects may be animated
   Created by Julian Miller in Jan 2013 */

#include <graphics_lib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

#define XWINDOW 640
#define YWINDOW 480
#define TICK    0.5
#define RADIUS  10
#define XMAX    XWINDOW - RADIUS
#define XMIN    RADIUS
#define YMAX    YWINDOW - RADIUS
#define YMIN    5*RADIUS
#define MAXCOUNT 10000

/* make a data type hold position and velocity */
typedef struct
{
    double    pos;
    double    vel;
} posvel;


posvel hit_boundary(double pos, double vel, int isx);

/* handle what happens to balls at boundaries
   of the graphics window */
posvel hit_boundary(double pos, double vel, int isx)
{
    posvel z;

    z.pos = pos;
    z.vel = vel;

    if (isx)
    {
        if (pos < XMIN)
        {
            z.pos = XMIN;
            z.vel = -vel;
        }
        else if (pos > XMAX)
        {
            z.pos = XMAX;
            z.vel = -vel;
        }
    }
    else
    {
        if (pos < YMIN)
        {
            z.pos = YMIN;
            z.vel = -vel;
        }

        if (pos > YMAX)
        {
            z.pos = YMAX;
            z.vel = -vel;
        }
    }

    return z;
}


int main(void)
{
    int count = 0;
    double x1_old, y1_old;
    double x2_old, y2_old;
    double x1_new, y1_new;
    double x2_new, y2_new;
    double vx, vy, wx, wy;
    posvel  pv;

    x1_old = 100.0;
    y1_old = 100.0;
    vx = 10.0;
    vy = 5.0;

    x2_old = 250.0;
    y2_old = 250.0;
    wx = -8.0;
    wy = 4.0;

    /* open the graphics window */
    initwindow(XWINDOW, YWINDOW);

    /* allow mouse operations */
	initmouse();

    /* create an event queue */
    create_event_queue();

    /* register display and mouse as event sources */
    reg_display_events();
    reg_mouse_events();

    /* initialize the font */
    initfont();

    outtextxy(4,5,"To quit press left mouse button or close graphics window.");
    outtextxy(4,15,"To pause press right mouse button.");

	do
	{
	    /* calculate new ball positions */
        x1_new = x1_old + vx*TICK;
        y1_new = y1_old + vy*TICK;
        x2_new = x2_old + wx*TICK;
        y2_new = y2_old + wy*TICK;

        /* handle what to do if balls hit boundaries */
        pv = hit_boundary(x1_new, vx, 1);
        x1_new = pv.pos;
        vx = pv.vel;

        pv = hit_boundary(x2_new, wx, 1);
        x2_new = pv.pos;
        wx = pv.vel;

        pv = hit_boundary(y1_new, vy, 0);
        y1_new = pv.pos;
        vy = pv.vel;

        pv = hit_boundary(y2_new, wy, 0);
        y2_new = pv.pos;
        wy = pv.vel;

        /* draw balls on screen buffer in new positions */
        filled_circle(x1_new, y1_new, RADIUS , BLUE);
        filled_circle(x2_new, y2_new, RADIUS , RED);

        /* make the balls visible on the screen display
           and remove the balls in the previous positions */
        update_display();

        /* remove the balls in the previous positions on
           the screen buffer */
        filled_circle(x1_old, y1_old, RADIUS , BLACK);
        filled_circle(x2_old, y2_old, RADIUS , BLACK);

        /* update the old positions */
        x1_old = x1_new;
        y1_old = y1_new;
        x2_old = x2_new;
        y2_old = y2_new;

        count++;
        pausefor(8); /* wait 8 miliseconds */

        if (check_if_event())
        {
            /* wait for event  */
            wait_for_event();

            if (event_close_display())
                break;
            else if (event_mouse_button_down())
            {
                if (event_mouse_left_button_down())
                    break;
                else if (event_mouse_right_button_down())
                    wait_for_event();
            }
        }

	}
    while (count < MAXCOUNT);

    /* close the mouse */
    closemouse();


    /* remove the display */
    closegraph();


    return 0;
}

