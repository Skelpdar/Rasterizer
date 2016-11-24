#include "Rasterizer.h"
#include "Octant.h"

/**
Sets the color of a pixel (x,y) to color col.

pitch is the number bytes per row of pixels, from surf-pitch
bpp is the number of byters per pixel, from surf->format->BytesPerPixel
*/
void Rasterizer::setpixel( int x, int y,
	Color col, int pitch, int bpp) {

	if (x >= 0 && x < surf->w && y >= 0 && y < surf->h) {
		Uint8* p = (Uint8*)surf->pixels + y*pitch + x*bpp;
		*(p) = col.B;
		*(p + 1) = col.G;
		*(p + 2) = col.R;
	}
}


/**
Line drawing with bresenhams line drawing algorithm between two points (x1,y1) and (x2,y2).
*/
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
		setpixel(pos[0], pos[1], col, pitch, bpp);

		error += k;

		if (error > 1) {
			y += 1;
			error -= 1;
		}
	}
}

/**
Returns twice the area of the triangle with points (ax,ay), (ba,by) and (px,py).
*/
int Rasterizer::signedArea(int ax, int ay, int bx, int by, int px, int py) {
	return (bx - ax)*(py - ay) - (by - ay)*(px - ax);
}

/**
Draw a triangle between three points (x1,y1), (x2,y2) and (x3,y3) in screen coordinates.
*/
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

	int a01 = y1 - y2;
	int a12 = y2 - y3;
	int a20 = y3 - y1;

	int b01 = x2 - x1;
	int b12 = x3 - x2;
	int b20 = x1 - x3;

	int w0_row = signedArea(x2, y2, x3, y3, minX, minY);
	int w1_row = signedArea(x3, y3, x1, y1, minX, minY);
	int w2_row = signedArea(x1, y1, x2, y2, minX, minY);


	for (int y = minY; y <= maxY; y++) {

		int w0 = w0_row;
		int w1 = w1_row;
		int w2 = w2_row;

		for (int x = minX; x <= maxX; x++) {

			if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
				setpixel(x, y, col, pitch, bpp);
			}

			w0 += a12;
			w1 += a20;
			w2 += a01;
		}

		w0_row += b12;
		w1_row += b20;
		w2_row += b01;
	}

}