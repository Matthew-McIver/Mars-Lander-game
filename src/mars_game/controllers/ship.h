#ifndef __SHIPCONTROLLER_H__
#define __SHIPCONTROLLER_H__

#include "../models/ship.h"

typedef struct {
    Ship *ship;
    float targetAngle;
} ShipController;

#endif // __SHIPCONTROLLER_H__
