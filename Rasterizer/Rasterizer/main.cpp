#include <iostream>
#include <SDL.h>
#include "Color.h"
#include "Matrix.h"
#include <vector>
#include <iterator>
#include "Model.h"
#include <string>
#include "Rasterizer.h"
#include "Octant.h"
#include "Camera.h"

int main(int, char**) {

	//SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Rasterizer", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Pixel buffer
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	int bpp = surface->format->BytesPerPixel;
	int pitch = surface->pitch;
	int bpr = pitch / bpp;

	//Initialization of the renderer
	Rasterizer rasterizer;
	rasterizer.setPitch(pitch);
	rasterizer.setBpp(bpp);
	rasterizer.setSurface(surface);

	//Scene initialization
	Model model;
	model.loadFromFile("model.txt");
	model.position = Matrix(0, 0, 5);
	model.scale = Matrix(1, 1, 1);

	Model model2;
	model2.loadFromFile("model.txt");
	Matrix position(5, 0, 20);
	model2.position = position;
	model2.scale = Matrix(1, 1, 1);

	std::vector<Model*> modellist;
	modellist.push_back(&model);
	//modellist.push_back(&model2);

	Camera camera;
	camera.position = Matrix(0, 0, 0);
	camera.rotation = Matrix(0, 0, 0);

	bool runProgram = true;

	Color c(255, 255, 0, 0);

	float frameduration = 0;

	while (runProgram){
		
		SDL_PumpEvents();

		int starttime = SDL_GetTicks();

		

		//Event loop
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.key.keysym.sym == SDLK_s) {
				camera.position.matrix[2] -= 0.1;
			}
			if (e.key.keysym.sym == SDLK_w) {
				camera.position.matrix[2] += 0.1;
			}
			if (e.key.keysym.sym == SDLK_a) {
				camera.position.matrix[0] -= 0.1;
			}
			if (e.key.keysym.sym == SDLK_d) {
				camera.position.matrix[0] += 0.1;
			}
			if (e.key.keysym.sym == SDLK_q) {
				camera.rotation.matrix[1] -= 1;
			}
			if (e.key.keysym.sym == SDLK_e) {
				camera.rotation.matrix[1] += 1;
			}
		}

		SDL_LockSurface(surface);

		/*
		RENDER LOOP

		Begin with clearing the pixelbuffer

		Then render the scene by iterating, trough every model, and rasterize all of their faces.

		Lastly we update the screen

		*/
		
		//Clear the pixelbuffer by filling it with black
		SDL_FillRect(surface, NULL, 0x000000);

		//Iterate through every model, TODO redo all of this
		for (std::vector<Model*>::iterator modeliter = modellist.begin(); modeliter != modellist.end(); modeliter++) {
			

			//Setting up the individual matrices
			Matrix4 translate;
			translate.initialize_translation((*modeliter)->position.matrix[0], model.position.matrix[1], model.position.matrix[2]);
			Matrix4 scale;
			scale.initialize_scaling((*modeliter)->scale.matrix[0], model.scale.matrix[1], model.scale.matrix[2]);
			Matrix4 rotatex;
			rotatex.initialize_rotate_x((*modeliter)->rotation.matrix[0]);
			Matrix4 rotatey;
			rotatey.initialize_rotate_y((*modeliter)->rotation.matrix[1]);
			Matrix4 rotatez;
			rotatez.initialize_rotate_z((*modeliter)->rotation.matrix[2]);
			Matrix4 cameratrans;
			cameratrans = camera.getTranslationMatrix();
			Matrix4 cameraxrot;
			cameraxrot = camera.getXRotationMatrix();
			Matrix4 camerayrot;
			camerayrot = camera.getYRotationMatrix();
			Matrix4 camerazrot;
			camerazrot = camera.getZRotationMatrix();

			//Setting up the transformation matrix
			Matrix4 transmatrix = cameraxrot.mult(camerayrot);
			transmatrix = transmatrix.mult(camerazrot);
			transmatrix = transmatrix.mult(cameratrans);
			transmatrix = transmatrix.mult(translate);
			transmatrix = transmatrix.mult(scale);
			transmatrix = transmatrix.mult(rotatex);
			transmatrix = transmatrix.mult(rotatey);
			transmatrix = transmatrix.mult(rotatez);

			//Iterate through every face
			for (std::vector<Face*>::iterator faceiter = (*modeliter)->faces.begin(); faceiter != (*modeliter)->faces.end(); faceiter++) {
				
				std::vector<int> xvec;
				std::vector<int> yvec;

				//Iterate through every vertex
				for (std::vector<Vertex*>::iterator vertiter = (*faceiter)->vertices.begin(); vertiter != (*faceiter)->vertices.end(); vertiter++) {
					std::vector<float> pos = transmatrix.mult((*vertiter)->position).matrix;
					//Setpixel(surface, (pos[0] / pos[2] * 500 + 320), -(pos[1] / pos[2])* 500 + 240, c, pitch, bpp);
					xvec.push_back(pos[0] / pos[2] * 500 + 320);
					yvec.push_back(-(pos[1] / pos[2]) * 500 + 240);
				}

				//rasterizer.DrawLine(xvec[0], yvec[0], xvec[1], yvec[1], c);
				//rasterizer.DrawLine(xvec[1], yvec[1], xvec[2], yvec[2], c);
				//rasterizer.DrawLine(xvec[2], yvec[2], xvec[0], yvec[0], c);

				rasterizer.DrawTriangle(xvec[0], yvec[0], xvec[1], yvec[1], xvec[2], yvec[2], (*faceiter)->color);
			}
		}


		SDL_UnlockSurface(surface);

		SDL_UpdateWindowSurface(window);

		// TODO timings
		frameduration = SDL_GetTicks() - starttime;

		SDL_Delay(5);

		model.rotation.matrix[0] += 1;
		model.rotation.matrix[1] += 1;
		model.rotation.matrix[2] += 1;
		
	}
	
	return 0;
}