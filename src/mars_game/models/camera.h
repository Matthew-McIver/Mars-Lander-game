#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector.h"

typedef struct {
    Vector pos;
    double zoomScale;
} Camera;

Camera *mainCamera;

Vector WorldSpaceToCameraSpace(Camera *C, Vector X);

#endif // __CAMERA_H__
