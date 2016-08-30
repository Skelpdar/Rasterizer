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

	Matrix4 mat4;
	mat4.initialize_scaling(1, 1, 1);

	Matrix4 m4;
	m4.initialize_translation(1, 2, 3);

	Matrix4 newm4 = m4.mult(mat4);

	Matrix mat;
	mat.matrix.clear();
	mat.matrix.push_back(1);
	mat.matrix.push_back(1);
	mat.matrix.push_back(10);
	mat.matrix.push_back(1);

	Matrix newmat = newm4.mult(mat);
	for (int i = 0; i < 4; i++) {
		std::cout << newmat.matrix[i] << std::endl;
	}

	float x = newmat.matrix[0] / newmat.matrix[2] * 640 + 640 / 2;
	float y = newmat.matrix[1] / newmat.matrix[2] * -480 + 480 / 2;

	std::cout << x << " " << y << std::endl;
	 /*
	Setpixel(surface, x, y, c, pitch, bpp);
	*/

	SDL_UnlockSurface(surface);

	SDL_UpdateWindowSurface(window);

	
	// TODO timings
	SDL_Delay(2000);
	
	return 0;
}