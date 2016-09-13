#ifndef OCTANT_H
#define OCTANT_H

int DetermineOctant(float x1, float y1, float x2, float y2);

float* ToOctantZero(int octant, float x, float y);

float* FromOctantZero(int octant, float x, float y);

#endif