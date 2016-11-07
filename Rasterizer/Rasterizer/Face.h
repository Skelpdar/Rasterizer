#ifndef FACE_H
#define FACE_H

#include "Vertex.h"
#include <vector>
#include "Color.h"

class Face {
public:
	std::vector<Vertex*> vertices;
	Color color;

	void addVertex(Vertex* v);
	void setColor(Color c) { color = c; };

	Face() {};
	Face(std::vector<Vertex*> a);
	
};

#endif