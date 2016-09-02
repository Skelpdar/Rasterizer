#include "Setpixel.h"

void Setpixel(SDL_Surface* surf, int x, int y, 
	Color col,int pitch, int bpp) {

	if (x >= 0 && x < surf->w && y >= 0 && y < surf->h) {
		Uint8* p = (Uint8*)surf->pixels + y*pitch + x*bpp;
		*(p) = col.B;
		*(p + 1) = col.G;
		*(p + 2) = col.R;
	}
}