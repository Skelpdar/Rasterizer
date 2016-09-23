#include "Face.h"

void Face::addVertex(Vertex* v) {
	vertices.push_back(v);
}

Face::Face(std::vector<Vertex*> a) {
	vertices = a;
}