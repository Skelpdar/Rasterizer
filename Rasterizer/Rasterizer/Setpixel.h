#ifndef SETPIXEL_H
#define SETPIXEL_H

#include <SDL.h>
#include "Color.h"

void Setpixel(SDL_Surface* surf, int x, int y, 
	Color col, int pitch, int bpp);

#endif