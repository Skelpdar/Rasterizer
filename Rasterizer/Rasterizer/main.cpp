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
#include <cmath>
#include "Eigen/Core"

int main(int, char**) {

	int width = 640;
	int height = 480;
	int farplane = 10;

	//SDL Initialization
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Rasterizer", 100, 100, width, height, SDL_WINDOW_SHOWN);
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

	//Empty z-buffer
	std::vector<std::vector<float>> emptybuffer;
	for (int i = 0; i < width; i++) {
		std::vector<float> column;
		for (int j = 0; j < height; j++) {
			column.push_back(farplane);
		}
		emptybuffer.push_back(column);
	}

	//Initialization of the renderer
	Rasterizer rasterizer;
	rasterizer.setPitch(pitch);
	rasterizer.setBpp(bpp);
	rasterizer.setSurface(surface);

	//Scene initialization
	Model model;
	model.loadFromFile("model.txt");
	model.position = Eigen::Vector4f(0,0,0,1);
	model.scale = Eigen::Vector4f(1, 1, 1, 1);
	model.rotation = Eigen::Vector4f(0, 0, 0, 1);

	std::vector<Model*> modellist;
	modellist.push_back(&model);

	Camera camera;
	camera.position = Eigen::Vector4f(0, 0, -5, 1);
	camera.rotation = Eigen::Vector4f(0, 0, 0, 1);

	bool runProgram = true;

	Color c(255, 255, 0, 0);

	float frameduration = 0;

	int frame = 0;
	float framelength = 0;
	
	while (runProgram){
		
		SDL_PumpEvents();

		int starttime = SDL_GetTicks();

		SDL_LockSurface(surface);

		/*
		RENDER LOOP

		Begin with clearing the pixelbuffer and clearing the z-buffer

		Then render the scene by iterating, trough every model, and rasterize all of their faces.

		Lastly we update the screen

		*/
		
		//Clear the pixelbuffer by filling it with black
		SDL_FillRect(surface, NULL, 0x000000);

		//Reset the z-buffer
		rasterizer.setZBuffer(emptybuffer);

		//Iterate through every model, TODO redo all of this
		for (std::vector<Model*>::iterator modeliter = modellist.begin(); modeliter != modellist.end(); modeliter++) {
			
			Eigen::Matrix4f camy = camera.getYRotationMatrix();
			Eigen::Matrix4f camx = camera.getXRotationMatrix();
			Eigen::Matrix4f camtrans = camera.getTranslationMatrix();
			Eigen::Matrix4f trans = translation((*modeliter)->position(0, 0), (*modeliter)->position(1, 0), (*modeliter)->position(2, 0));
			Eigen::Matrix4f scl = scale((*modeliter)->scale(0, 0), (*modeliter)->scale(1, 0), (*modeliter)->scale(2, 0));
			Eigen::Matrix4f rotx = rotatex((*modeliter)->rotation(0, 0));
			Eigen::Matrix4f roty = rotatey((*modeliter)->rotation(1, 0));
			Eigen::Matrix4f rotz = rotatez((*modeliter)->rotation(2, 0));

			Eigen::Matrix4f transmatrix = camy * camx * camtrans * trans * scl * rotx * roty * rotz;

			//Iterate through every face
			for (std::vector<Face*>::iterator faceiter = (*modeliter)->faces.begin(); faceiter != (*modeliter)->faces.end(); faceiter++) {
				
				std::vector<int> xvec;
				std::vector<int> yvec;

				std::vector<float> depth;

				//Iterate through every vertex
				for (std::vector<Vertex*>::iterator vertiter = (*faceiter)->vertices.begin(); vertiter != (*faceiter)->vertices.end(); vertiter++) {

					Eigen::Vector4f pos = transmatrix * (*vertiter)->position;

					//Draws vertices
					//rasterizer.setpixel((pos[0] / pos[2] * 500 + 320), -(pos[1] / pos[2])* 500 + 240, c, pitch, bpp);
					//TODO: Proper projection
					xvec.push_back(static_cast<int>(pos(0,0) / pos(2,0) * 500 + width/2));
					yvec.push_back(static_cast<int>(-(pos(1,0) / pos(2,0)) * 500 + height/2));

					depth.push_back( sqrt(pow(pos(0,0), 2) + pow(pos(1,0),2)  + pow(pos(2,0),2) ));

				}

				//Draws lines
				//rasterizer.DrawLine(xvec[0], yvec[0], xvec[1], yvec[1], c);
				//rasterizer.DrawLine(xvec[1], yvec[1], xvec[2], yvec[2], c);
				//rasterizer.DrawLine(xvec[2], yvec[2], xvec[0], yvec[0], c);

				rasterizer.DrawTriangle(xvec, yvec, (*faceiter)->color, depth);

			}

		}

		SDL_UnlockSurface(surface);

		SDL_UpdateWindowSurface(window);

		// TODO timings
		frameduration = SDL_GetTicks() - starttime;

		frame++;
		framelength += frameduration;
		if (frame >= 50) {
			std::cout << 1000 / (framelength / 50) << std::endl;
			frame = 0;
			framelength = 0;
		}

		//SDL_Delay(0);

		//model.rotation(0, 0) += 1;
		//model.rotation(1, 0) += 1;
		model.rotation(2, 0) += 1;
		
	}

	
	return 0;
}