#include "Rasterizer.h"
#include "Octant.h"

Rasterizer::Rasterizer() {
	
}

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
void Rasterizer::DrawTriangle( std::vector<int> xvec, std::vector<int> yvec, Color col, std::vector<float> depth) {

	int minX = std::min(xvec[0], xvec[1]);
	minX = std::min(minX, static_cast<int>(xvec[2]));
	minX = std::max(minX, 0);

	int maxX = std::max(xvec[0], xvec[1]);
	maxX = std::max(maxX, static_cast<int>(xvec[2]));
	maxX = std::min((surf->w - 1), maxX);

	int minY = std::min(yvec[0], yvec[1]);
	minY = std::min(minY, static_cast<int>(yvec[2]));
	minY = std::max(minY, 0);

	int maxY = std::max(yvec[0], yvec[1]);
	maxY = std::max(maxY, static_cast<int>(yvec[2]));
	maxY = std::min(surf->h - 1, maxY);
		
	int a01 = yvec[0] - yvec[1];
	int a12 = yvec[1] - yvec[2];
	int a20 = yvec[2] - yvec[0];

	int b01 = xvec[1] - xvec[0];
	int b12 = xvec[2] - xvec[1];
	int b20 = xvec[0] - xvec[2];

	int w0_row = signedArea(xvec[1], yvec[1], xvec[2], yvec[2], minX, minY);
	int w1_row = signedArea(xvec[2], yvec[2], xvec[0], yvec[0], minX, minY);
	int w2_row = signedArea(xvec[0], yvec[0], xvec[1], yvec[1], minX, minY);

	//TODO: Clean this up
	float za = ((yvec[1] - yvec[2])*(xvec[0] - xvec[2]) + (xvec[2] - xvec[1])*(yvec[0] - yvec[2]));

	float zb = yvec[1] - yvec[2];
	float zc = xvec[2] - xvec[1];

	float zd = yvec[2] - yvec[0];
	float ze = xvec[0] - xvec[2];

	float zw1row = ((yvec[1] - yvec[2])*(minX - xvec[2]) + (xvec[2] - xvec[1])*(minY - yvec[2])) / za;
	float zw1x = (yvec[1] - yvec[2]) / za;
	float zw1y = (xvec[2] - xvec[1]) / za;

	float zw2row = ((yvec[2] - yvec[0])*(minX - xvec[2]) + (xvec[0] - xvec[2])*(minY - yvec[2])) / za;
	float zw2x = zd / za;
	float zw2y = ze / za;

	float zw3row = 1 - zw1row - zw2row;
	float zw3x = -(zb + zd) / za;
	float zw3y = -(zc + ze) / za;

	float zrow = zw1row*depth[0] + zw2row*depth[1] + zw3row*depth[2];
	float zx = depth[0] * zw1x + depth[1] * zw2x + depth[2] * zw3x;
	float zy = depth[0] * zw1y + depth[1] * zw2y + depth[2] * zw3y;

	if (za != 0) {
		for (int y = minY; y <= maxY; y++) {

			int w0 = w0_row;
			int w1 = w1_row;
			int w2 = w2_row;

			//float zw1 = zw1row;
			//float zw2 = zw2row;
			//float zw3 = zw3row;

			float z = zrow;

			for (int x = minX; x <= maxX; x++) {

				if (w0 >= 0 && w1 >= 0 && w2 >= 0) {

					//zw1 = ((yvec[1] - yvec[2])*(x - xvec[2]) + (xvec[2] - xvec[1])*(y - yvec[2])) / za;
					//zw2 = ((yvec[2] - yvec[0])*(x - xvec[2]) + (xvec[0] - xvec[2])*(y - yvec[2])) / za;
					//zw3 = 1 - zw1 - zw2;
					//z = zw1*depth[0] + zw2*depth[1] + zw3*depth[2];

					if (zBuffer[x][y] > z) {
						//int hue = z / 10 * 255;

						//col.R = hue;
						//col.G = hue;
						//col.B = hue;

						setpixel(x, y, col, pitch, bpp);
						zBuffer[x][y] = z;
					}
				}

				w0 += a12;
				w1 += a20;
				w2 += a01;

				//zw1 += zw1x;
				//zw2 += zw2x;
				//zw3 += zw3x;

				z += zx;

			}

			w0_row += b12;
			w1_row += b20;
			w2_row += b01;

			//zw1row += zw1y;
			//zw2row += zw2y;
			//zw3row += zw3y;

			zrow += zy;

		}
	}

}