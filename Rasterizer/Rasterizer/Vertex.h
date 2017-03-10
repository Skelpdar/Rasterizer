#ifndef VERTEX_H
#define VERTEX_H

#include "Matrix.h"
#include "Eigen/Core"

/**
A vertex only holds its spatial coordinates
*/
class Vertex {
public:
	Eigen::Vector4f position;

	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

	Vertex();
	Vertex(float x, float y, float z);
	void setPos(float x, float y, float z);
};

#endif