#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stdio.h>

typedef struct {
    float x, y;
} Vector;

Vector NewVector(double x, double y);

Vector NewPolarVector(double angle, double length);

Vector difference(Vector a, Vector b);

float length2(Vector a);

float length(Vector a);

Vector normalise(Vector a);

Vector multiply(Vector a, float b);

#endif // __VECTOR_H__
