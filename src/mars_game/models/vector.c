#include <stdio.h>
#include <math.h>
#include "vector.h"

Vector NewVector(double x, double y) {
    Vector *v = malloc(sizeof *v);
    v->x = x;
    v->y = y;
    return *v;
};

Vector NewPolarVector(double angle, double length) {
    Vector *v = malloc(sizeof *v);
    v->x = length * sin(angle);
    v->y = length * cos(angle);
    return *v;
};

Vector difference(Vector a, Vector b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    Vector diff = {dx, dy};
    return diff;
};

float length2(Vector a) {
    float len2 = (a.x*a.x) + (a.y*a.y);
    return len2;
};

float length(Vector a) {
    float len2 = length2(a);
    float len = sqrt(len2);
    return len;
}

Vector normalise(Vector a) {
    float len = length(a);
    float x = a.x/len;
    float y = a.y/len;
    Vector b = {x, y};
    return b;
};

Vector multiply(Vector a, float b) {
    float x = a.x * b;
    float y = a.y * b;
    Vector c = {x, y};
    return c;
};

Vector translate(Vector a, Vector b) {
    Vector c = {a.x + b.x, a.y + b.y};
};
