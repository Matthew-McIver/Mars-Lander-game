#include "../models/vector.h"
#include "../models/body.h"
#include "../models/camera.h"
#include "../models/ship.h"
#include "view.h"
#include "strings.h"

View *NewView(char filename[]) {
    View *v = malloc(sizeof *v);
    char *file = malloc(sizeof *file);
    sprintf(file, "%s%s%s", graphicsDir, filename, fileExt);
    v->sprite = al_load_bitmap(file);
    v->fail = !(v->sprite);
    return v;
}

void Render(View *this) {
    Vector pos = WorldSpaceToCameraSpace(mainCamera, this->body->position);
    al_draw_scaled_rotated_bitmap(this->sprite, 100, 30, pos.x, pos.y, 2E-4*mainCamera->zoomScale, 2E-4*mainCamera->zoomScale, Player->Angle, 0);
    al_flip_display();
}
