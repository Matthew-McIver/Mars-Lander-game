#include "camera.h"
#include "vector.h"

void Centre(Camera *C, Vector X) {
    C->pos = X;
};

Vector WorldSpaceToCameraSpace(Camera *C, Vector X) {
    double x = (X.x - C->pos.x)/C->zoomScale;
    double y = (C->pos.y - X.y)/C->zoomScale;
    Vector v = {x, y};
    return v;
};
