#ifndef MODEL_H
#define MODEL_H

#include "Matrix.h"
#include "Face.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Eigen/Core"

class Model {
	std::vector<std::string> split(std::string);
public:
	Eigen::Vector4f position;
	Eigen::Vector4f scale;
	Eigen::Vector4f rotation;

	std::vector<Face*> faces;

	void loadFromFile(std::string filename);

	Model(std::vector<Face*> a);
	Model();
};

#endif