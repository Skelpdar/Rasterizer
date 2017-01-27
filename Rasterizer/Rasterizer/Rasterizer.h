#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <SDL.h>
#include "Color.h"
#include "Face.h"
#include <algorithm>

/**
Used to draw on a SDL_Surface.
setSurface, setBpp and setPitch need to be set before use.
*/
class Rasterizer {
	int pitch;
	int bpp;
	SDL_Surface* surf;
	int signedArea(int ax, int ay, int bx, int by, int cx, int cy);
	std::vector<std::vector<float>> zBuffer;

public:

	Rasterizer();

	void setPitch(int p) { pitch = p; }

	void setBpp(int b) { bpp = b; }

	void setSurface(SDL_Surface* s) { surf = s; }

	void setZBuffer(std::vector<std::vector<float>> z) { zBuffer = z; }

	void setpixel(int x, int y,
		Color col, int pitch, int bpp);

	void DrawLine( int x1, int y1, int x2,
		int y2, Color col);

	void DrawTriangle( std::vector<int> xvec, std::vector<int> yvec, Color col, std::vector<float> depth);

};

#endif