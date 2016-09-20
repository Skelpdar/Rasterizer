#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <SDL.h>
#include "Color.h"
#include "Setpixel.h"
#include "Face.h"

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
	void DrawTriangle(SDL_Surface* surf, Face f);

};

#endif