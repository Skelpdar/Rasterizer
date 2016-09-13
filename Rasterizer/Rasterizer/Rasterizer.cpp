#include "Rasterizer.h"
#include "Octant.h"

void DrawLine(SDL_Surface* surf, int x1, int y1, int x2, int y2, Color col, int pitch, int bpp) {
	int octant = DetermineOctant(x1, y1, x2, y2);

	float* startpos = ToOctantZero(octant, x1, y1);
	x1 = startpos[0];
	y1 = startpos[1];

	float* endpos = ToOctantZero(octant, x2, y2);
	x2 = endpos[0];
	y2 = endpos[1];

	float error = 0;
	float y = y1;
	
	float dx = x2 - x1;
	float dy = y2 - y1;

	float k = dy / dx;

	int xpositive = 1;

	for (int i = x1; i < x2 - 1; i++) {
		float* pos = FromOctantZero(octant, i, y);
		Setpixel(surf, pos[0], pos[1], col, pitch, bpp);

		error += k;

		if (error > 1) {
			y += 1;
			error -= 1;
		}

	}
}