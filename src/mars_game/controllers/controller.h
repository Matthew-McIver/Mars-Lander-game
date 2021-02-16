#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#define NUM_CONTROLLERS 1

typedef struct {
    //void (*Start) (void *this);
    void (*Update)(void *this, double time);
    void *controller;
} Controller;

void Update(Controller *c, double time);

#endif // __CONTROLLER_H__
