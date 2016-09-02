#ifndef FACE_H
#define FACE_H

#include "Vertex.h"
#include <vector>

class Face {
public:
	std::vector<Vertex*> vertices;
	
	Face(std::vector<Vertex*> a);
};

#endif