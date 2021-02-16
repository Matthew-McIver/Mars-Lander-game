#ifndef __SHIP_H__
#define __SHIP_H__

#include "body.h"

typedef struct {
    double DryMass;
    double Fuel;
    double ExhaustVelocity;
    double Angle;
    float throttle;
    Body *body;
} Ship;

Ship *Player;

Ship *NewShip(Body *body, double DryMass, double Fuel, double ExhaustVelocity);

void UpdateMass(Ship *Ship);

void BurnFuel(Ship *Ship, double Fuel, double time);

#endif // __SHIP_H__
