#include <iostream>
#include <SDL.h>
#include "Color.h"
#include "Setpixel.h"
#include "Matrix.h"
#include <vector>
#include <iterator>


// Beware: Chaos
int main(int, char**) {

	//SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Surface* surface = SDL_GetWindowSurface(window);

	int bpp = surface->format->BytesPerPixel;
	int pitch = surface->pitch;
	int bpr = pitch / bpp;

	//Program loop TODO
	//Rendering
	SDL_LockSurface(surface);

	Color c(0, 0, 255, 0);

	for (int x = 0; x < 100; x++) {
		Setpixel(surface, x, x, c, pitch, bpp);
	}

	SDL_UnlockSurface(surface);

	SDL_UpdateWindowSurface(window);

	Matrix4 mat4;
	mat4.initialize_rotate_z(90);

	Matrix mat;
	mat.matrix.clear();
	mat.matrix.push_back(1);
	mat.matrix.push_back(2);
	mat.matrix.push_back(3);
	mat.matrix.push_back(1);

	Matrix newmat = mat4.mult(mat);
	for (int i = 0; i < 4; i++) {
		std::cout << newmat.matrix[i] << std::endl;
	}

	
	// TODO timings
	SDL_Delay(2000);
	
	return 0;
}