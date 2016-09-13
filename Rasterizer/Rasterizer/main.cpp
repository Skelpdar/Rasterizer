#include <iostream>
#include <SDL.h>
#include "Color.h"
#include "Setpixel.h"
#include "Matrix.h"
#include <vector>
#include <iterator>
#include "Model.h"
#include <string>
#include "Rasterizer.h"
#include "Octant.h"

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

	std::vector<Model*> modellist;

	//garbage

	Vertex v1(1.0, 1.0, 1.0);
	Vertex v2(1.0, -1.0, 1.0);
	Vertex v3(-1.0, 1.0, 1.0);
	Vertex v4(-1.0, -1.0, 1.0);

	std::vector<Vertex*> face;
	face.push_back(&v1);
	face.push_back(&v2);
	face.push_back(&v3);

	Face f1(face);

	face.clear();
	face.push_back(&v2);
	face.push_back(&v3);
	face.push_back(&v4);

	Face f2(face);


	std::vector<Face*> faces;
	faces.push_back(&f1);
	faces.push_back(&f2);

	Model model(faces);

	model.position.matrix.clear();
	model.position.matrix.push_back(0);
	model.position.matrix.push_back(0);
	model.position.matrix.push_back(5);

	model.scale.matrix.clear();
	model.scale.matrix.push_back(1);
	model.scale.matrix.push_back(1);
	model.scale.matrix.push_back(1);

	model.rotation.matrix.clear();
	model.rotation.matrix.push_back(0);
	model.rotation.matrix.push_back(0);
	model.rotation.matrix.push_back(0);

	modellist.push_back(&model);

	bool runProgram = true;

	Color c(255, 255, 0, 0);

	//Program loop TODO
	//Rendering
	while (runProgram){
		
		SDL_PumpEvents();

		int starttime = SDL_GetTicks();

		SDL_LockSurface(surface);

		SDL_FillRect(surface, NULL, 0x000000);

		DrawLine(surface, 10, 100, 10, 10, c, pitch, bpp);

		//Iterate through every model, TODO redo all of this
		for (std::vector<Model*>::iterator modeliter = modellist.begin(); modeliter != modellist.end(); modeliter++) {
			//Iterate through every face
			Matrix4 translate;
			translate.initialize_translation(model.position.matrix[0], model.position.matrix[1], model.position.matrix[2]);
			Matrix4 scale;
			scale.initialize_scaling(model.scale.matrix[0], model.scale.matrix[1], model.scale.matrix[2]);
			Matrix4 rotatex;
			rotatex.initialize_rotate_x(model.rotation.matrix[0]);
			Matrix4 rotatey;
			rotatey.initialize_rotate_y(model.rotation.matrix[1]);
			Matrix4 rotatez;
			rotatez.initialize_rotate_z(model.rotation.matrix[2]);

			Matrix4 transmatrix = translate.mult(scale);
			transmatrix = transmatrix.mult(rotatex);
			transmatrix = transmatrix.mult(rotatey);
			transmatrix = transmatrix.mult(rotatez);

			for (std::vector<Face*>::iterator faceiter = (*modeliter)->faces.begin(); faceiter != (*modeliter)->faces.end(); faceiter++) {
				//Iterate through every vertex
				std::vector<int> xvec;
				std::vector<int> yvec;
				for (std::vector<Vertex*>::iterator vertiter = (*faceiter)->vertices.begin(); vertiter != (*faceiter)->vertices.end(); vertiter++) {
					std::vector<float> pos = transmatrix.mult((*vertiter)->position).matrix;
					Setpixel(surface, (pos[0] / pos[2] * 640 + 320), -(pos[1] / pos[2])* 480 + 240, c, pitch, bpp);
					xvec.push_back(pos[0] / pos[2] * 640 + 320);
					yvec.push_back(-(pos[1] / pos[2]) * 480 + 240);
				}
				DrawLine(surface, xvec[0], yvec[0], xvec[1], yvec[1], c, pitch, bpp);
				DrawLine(surface, xvec[1], yvec[1], xvec[2], yvec[2], c, pitch, bpp);
				DrawLine(surface, xvec[2], yvec[2], xvec[0], yvec[0], c, pitch, bpp);
			}
		}


		SDL_UnlockSurface(surface);

		SDL_UpdateWindowSurface(window);

		// TODO timings
		float frameduration = SDL_GetTicks() - starttime;

		SDL_Delay( 5 );

		//model.rotation.matrix[0] += 1;
		model.rotation.matrix[1] += 1;
		//model.rotation.matrix[2] += 1;



		//runProgram = false;
		
	}
	
	return 0;
}