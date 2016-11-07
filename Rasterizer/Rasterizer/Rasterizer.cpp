#include "Rasterizer.h"
#include "Octant.h"


void Rasterizer::DrawLine(int x1, int y1, int x2, int y2, Color col) {
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

	for (int i = x1; i < x2 ; i++) {
		float* pos = FromOctantZero(octant, i, y);
		Setpixel(surf, pos[0], pos[1], col, pitch, bpp);

		error += k;

		if (error > 1) {
			y += 1;
			error -= 1;
		}
	}
}

bool Rasterizer::signedArea(int ax, int ay, int bx, int by, int cx, int cy) {
	bool b = false;
	if ((bx - ax)*(cy - ay) - (by - ay)*(cx - ax) >= 0) {
		b = true;
		return b;
	}
	else {
		return b;
	}
}

void Rasterizer::DrawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, Color col) {
	int minX = std::min(x1, x2);
	minX = std::min(minX, x3);
	minX = std::max(minX, 0);

	int maxX = std::max(x1, x2);
	maxX = std::max(maxX, x3);
	maxX = std::min(surf->w - 1, maxX);

	int minY = std::min(y1, y2);
	minY = std::min(minY, y3);
	minY = std::max(minY, 0);

	int maxY = std::max(y1, y2);
	maxY = std::max(maxY, y3);
	maxY = std::min(surf->h - 1, maxY);

	for (int y = minY; y <= maxY; y++) {
		for (int x = minX; x <= maxX; x++) {
			bool w0 = signedArea(x2, y2, x1, y1, x, y);
			bool w1 = signedArea(x1, y1, x3, y3, x, y);
			bool w2 = signedArea(x3, y3, x2, y2, x, y);

			if (w0 && w1 && w2) {
				Setpixel(surf, x, y, col, pitch, bpp);
			}
		}
	}

}