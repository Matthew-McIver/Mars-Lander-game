#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "models/body.h"
#define n 2

struct Game
{
    ALLEGRO_FONT *myfont; /* Our font. */
    ALLEGRO_DISPLAY *display; /* Our display */
    ALLEGRO_EVENT_QUEUE *queue; /* Our events queue. */
    ALLEGRO_TIMER *timer; /* Our physics timer. */

    double FPS; /* How often to update per second. */

    bool first_tick;
    bool redraw;
    double this_time, prev_time, accum_time;
    double timer_events;

    Body *bodies[n];
} game;

#endif // __GAME_H__
