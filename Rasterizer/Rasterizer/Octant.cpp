#include "Octant.h"

//TODO Make this less ugly
int DetermineOctant(float x1, float y1, float x2, float y2) {
	int octant = 0;

	float dy = y2 - y1;
	float dx = x2 - x1;

	if (dy > 0) {
		if (dx >= 0) {
			if (dy / dx < 1) {
				octant = 0;
			}
			else {
				octant = 1;
			}
		}
		else {
			if (dy / dx < -1) {
				octant = 2;
			}
			else {
				octant = 3;
			}
		}
	}
	else {
		if (dx >= 0) {
			if (dy / dx > -1) {
				octant = 7;
			}
			else {
				octant = 6;
			}
		}
		else {
			if (dy / dx > 1) {
				octant = 5;
			}
			else {
				octant = 4;
			}
		}
	}

	return octant;
}

float* ToOctantZero(int octant, float x, float y) {
	float out[2];

	switch (octant) {

	case 0 :
		out[0] = x;
		out[1] = y;
		break;

	case 1:
		out[0] = y;
		out[1] = x;
		break;

	case 2:
		out[0] = y;
		out[1] = -x;
		break;

	case 3:
		out[0] = -x;
		out[1] = y;
		break;

	case 4:
		out[0] = -x;
		out[1] = -y;
		break;

	case 5:
		out[0] = -y;
		out[1] = -x;
		break;

	case 6:
		out[0] = -y;
		out[1] = x;
		break;

	case 7:
		out[0] = x;
		out[1] = -y;
		break;

	}

	return out;
}

float* FromOctantZero(int octant, float x, float y) {

	float out[2];

	switch (octant) {
	case 0:
		out[0] = x;
		out[1] = y;
		break;

	case 1:
		out[0] = y;
		out[1] = x;
		break;

	case 2:
		out[0] = -y;
		out[1] = x;
		break;

	case 3:
		out[0] = -x;
		out[1] = y;
		break;

	case 4:
		out[0] = -x;
		out[1] = -y;
		break;

	case 5:
		out[0] = -y;
		out[1] = -x;
		break;

	case 6:
		out[0] = y;
		out[1] = -x;
		break;

	case 7:
		out[0] = x;
		out[1] = -y;
		break;
	}

	return out;
}