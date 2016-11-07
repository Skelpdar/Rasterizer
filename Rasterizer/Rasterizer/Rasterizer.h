#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <SDL.h>
#include "Color.h"
#include "Setpixel.h"
#include "Face.h"
#include <algorithm>

class Rasterizer {
	int pitch;
	int bpp;
	SDL_Surface* surf;

public:
	void setPitch(int p) { pitch = p; }

	void setBpp(int b) { bpp = b; }

	void setSurface(SDL_Surface* s) { surf = s; }

	//Line drawing using Bresenham's line algorithm
	void DrawLine( int x1, int y1, int x2,
		int y2, Color col);

	//Draw triangles
	bool signedArea(int ax, int ay, int bx, int by, int cx, int cy);
	void DrawTriangle( int x1, int y1, int x2, int y2, int x3, int y3, Color col);

};

#endif