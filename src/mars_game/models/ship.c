#include <stdio.h>
#include <math.h>

#include "ship.h"
#include "vector.h"
#include "../controllers/physics.h"

Ship *NewShip(Body *body, double DryMass, double Fuel, double ExhaustVelocity){
    Ship *ship = malloc(sizeof *ship);
    ship->DryMass = DryMass;
    ship->Fuel = Fuel;
    ship->ExhaustVelocity = ExhaustVelocity;
    ship->Angle = 0;
    ship->throttle = 0;
    ship->body = body;
};

void UpdateMass(Ship *Ship) {
    double Mass = Ship->DryMass + Ship->Fuel;
    Ship->body->mass = Mass;
};

const double fuelNumber = 100;

void BurnFuel(Ship *Ship, double Fuel, double time) {
    if (Fuel == 0) {
        return;
    };
    Fuel = (Fuel > Ship->Fuel) ? Ship->Fuel : Fuel;
    Ship->Fuel -= Fuel / 2;
    UpdateMass(Ship);
    double Force = Ship->ExhaustVelocity * fuelNumber * Fuel / time;
    Vector acc = NewPolarVector(Ship->Angle, -Force / Ship->body->mass);
    applyAcceleration(Ship->body, acc, time);
    Ship->Fuel -= Fuel / 2;
};
