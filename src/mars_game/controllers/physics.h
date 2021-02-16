#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdio.h>
#include "../models/body.h"
#include "../models/vector.h"
#include "controller.h"

#define NUM_BODIES 2

typedef struct {
    Body *bodies;
} PhysicsController;

void pc_update(PhysicsController *this, double time);

Controller *pc_create(Body *bodies);

double grav_const;

Vector accelerationDueToGravity(Body a, Body b);

void doPhysics(Body *body, double time);

#endif // __PHYSICS_H__

