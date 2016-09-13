#ifndef RASTERIZER_H
#define RASTERIZER_H

#include <SDL.h>
#include "Color.h"
#include "Setpixel.h"

//Line drawing using Bresenham's line algorithm
void DrawLine(SDL_Surface* surf, int x1, int y1, int x2, 
	int y2, Color col, int pitch, int bpp);

#endif