#ifndef __BODY_H__
#define __BODY_H__

#include <stdio.h>
#include "vector.h"

typedef struct {
    float mass;
    Vector position;
    Vector velocity;
    struct Body* SphereOfInfluence;
} Body;

#endif // __BODY_H__
