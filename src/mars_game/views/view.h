#ifndef __VIEW_H__
#define __VIEW_H__

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

static const char graphicsDir[] = "data/mars_game/";
static const char fileExt[] = ".png";

typedef struct {
    ALLEGRO_BITMAP *sprite;
    bool fail;
    Body *body //TODO: remove so can render non-physics things
} View;

View *NewView(char filename[]);

#endif // __VIEW_H__
