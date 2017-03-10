#include "Vertex.h"

Vertex::Vertex(float x, float y, float z) {
	setPos(x, y, z);
}

void Vertex::setPos(float x, float y, float z) {
	position << x, y, z, 1;
}