#include "Model.h"

Model::Model(std::vector<Face*> a) {
	faces = a;
}

Model::Model() {

}

std::vector<std::string> Model::split(std::string str) {
	std::string buffer;
	std::stringstream stream(str);

	std::vector<std::string> words;

	while (stream >> buffer) {
		words.push_back(buffer);
	}

	return words;
}

//Currently does not support texture mapping, defining normals for faces
//nor materials, polygons have to be triangulated
void Model::loadFromFile(std::string filename) {
	faces.clear();

	std::vector<Vertex*> vertices;

	std::ifstream file(filename);

	std::string line;

	while (std::getline(file, line)) {

		std::vector<std::string> spl = split(line);

		if (spl.front() == "v") {

			float x = std::stod(spl[1]);
			float y = std::stod(spl[2]);
			float z = std::stod(spl[3]);

			Vertex* vert = new Vertex(x, y, z);

			vertices.push_back(vert);
		}

		if (spl.front() == "f") {

			Color* col = new Color(rand() % 255, rand() % 255, rand() % 255, 0);

			Face* face = new Face();

			face->setColor(*col);

			int vert1 = std::stoi(spl[1]);
			int vert2 = std::stoi(spl[2]);
			int vert3 = std::stoi(spl[3]);

			face->addVertex(vertices[vert3 - 1]);
			face->addVertex(vertices[vert2 - 1]);
			face->addVertex(vertices[vert1 - 1]);

			faces.push_back(face);

		}

	}

	file.close();

}
