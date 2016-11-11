#ifndef MODEL_H
#define MODEL_H

#include "Matrix.h"
#include "Face.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Model {
	std::vector<std::string> split(std::string);
public:
	Matrix position;
	Matrix scale;
	Matrix rotation;

	std::vector<Face*> faces;

	void loadFromFile(std::string filename);

	Model(std::vector<Face*> a);
};

#endif