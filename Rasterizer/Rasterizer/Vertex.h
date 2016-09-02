#ifndef VERTEX_H
#define VERTEX_H

#include "Matrix.h"

class Vertex {
public:
	Matrix position;

	Vertex();
	Vertex(float x, float y, float z);
	void setPos(float x, float y, float z);
};

#endif