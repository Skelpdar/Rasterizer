#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) {
	setPos(x, y, z);
}

void Vertex::setPos(float x, float y, float z) {
	position.matrix.clear();
	position.matrix.push_back(x);
	position.matrix.push_back(y);
	position.matrix.push_back(z);
	position.matrix.push_back(1);
}