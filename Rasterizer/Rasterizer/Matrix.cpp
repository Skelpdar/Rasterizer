#include "Matrix.h"

Matrix::Matrix() {
	for (int i = 0; i < 4; i++) {
		matrix.push_back(0.0);
	}
}

Matrix Matrix4::mult(Matrix m) {
	Matrix out;
	
	//TODO iterators?
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out.matrix[j] += m.matrix[i] * matrix[i][j];
		}
	}

	return out;
}

//Translating the initialization arrays to the matrix 
void Matrix4::array_to_matrix(float* a) {

	for (int i = 0; i < 4; i++) {
		std::vector<float> x;

		for (int j = 0; j < 4; j++) {
			x.push_back(a[j * 4 + i]);
		}
		matrix.push_back(x);
	}
}

void Matrix4::initialize_identity() {
	
	float a[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	array_to_matrix(a);
}

void Matrix4::initialize_translation(float x, float y, float z) {
	
	float a[16] = {
		1,0,0,x,
		0,1,0,y,
		0,0,1,z,
		0,0,0,1
	};

	array_to_matrix(a);
}

void Matrix4::initialize_scaling(float x, float y, float z) {

	float a[16] = {
		x,0,0,0,
		0,y,0,0,
		0,0,z,0,
		0,0,0,1
	};

	array_to_matrix(a);
}

void Matrix4::initialize_rotate_x(float t) {
	t = t * PI / 180;

	float a[16] = {
		1,0,0,0,
		0,cos(t),-sin(t),0,
		0,sin(t),cos(t),0,
		0,0,0,1
	};

	array_to_matrix(a);
}

void Matrix4::initialize_rotate_y(float t) {
	t = t * PI / 180;

	float a[16] = {
		cos(t),0,sin(t),0,
		0,1,0,0,
		-sin(t),0,cos(t),0,
		0,0,0,1
	};

	array_to_matrix(a);
}

void Matrix4::initialize_rotate_z(float t) {
	t = t * PI / 180;

	float a[16] = {
		cos(t),-sin(t),0,0,
		sin(t),cos(t),0,0,
		0,0,1,0,
		0,0,0,1
	};

	array_to_matrix(a);
}