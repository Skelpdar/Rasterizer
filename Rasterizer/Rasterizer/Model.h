#ifndef MODEL_H
#define MODEL_H

#include "Matrix.h"
#include "Face.h"
#include <vector>

class Model {
public:
	Matrix position;
	Matrix scale;
	Matrix rotation;

	std::vector<Face*> faces;

	Model(std::vector<Face*> a);
};

#endif