#include <stdio.h>
#include "physics.h"
#include "controller.h"
#include "../models/vector.h"
#include "../models/body.h"
#include "../models/ship.h"

double grav_const = 6.67408E-11;

Controller *pc_create(Body *bodies) {
    PhysicsController *pc = malloc(sizeof *pc);
    pc->bodies = bodies;
    Controller *c = malloc(sizeof *c);
    c->Update = pc_update;
    c->controller = pc;
    return c;
};

void pc_update(PhysicsController *this, double time){
    BurnFuel(Player, (1*Player->throttle), time);
    int i;
    for (i = 0; i < NUM_BODIES; i++) {
        //doGravity(&this->bodies[i], time);
        doMovement(&this->bodies[i], time);
    }
};

Vector accelerationDueToGravity(Body a, Body b) {
    Vector r = difference(b.position, a.position);
    float acc = grav_const * b.mass / length2(r);
    Vector accv = multiply(normalise(r), acc);
    return accv;
};

Vector applyAcceleration(Body *body, Vector acc, double time) {
    Vector dv = multiply(acc, time);
    float vx = body->velocity.x + dv.x;
    float vy = body->velocity.y + dv.y;
    Vector v = {vx, vy};
    body->velocity = v;
};

void doGravity(Body *body, double time) {
    Body *soi = body->SphereOfInfluence;
    if (&body == soi) {
        return;
    }
    Vector acc = accelerationDueToGravity(*body, *soi);
    applyAcceleration(body, acc, time);
};

void doMovement(Body *body, double time) {
    Vector d = multiply(body->velocity, time);
    float x = body->position.x + d.x;
    float y = body->position.y + d.y;
    Vector p = {x, y};
    body->position = p;
};
