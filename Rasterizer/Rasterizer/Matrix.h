#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>

#define PI 3.14159265

// 1x4 matrix for vertex position data
class Matrix {
public:
	std::vector<float> matrix;
	Matrix();
};

// The 4x4 transformation matrices
class Matrix4 {
public:
	//Outer vector is columns, inner is the rows
	std::vector< std::vector<float> > matrix;
	Matrix mult(Matrix m);
	void array_to_matrix(float* a);
	void initialize_identity();
	void initialize_translation(float x, float y, float z);
	void initialize_scaling(float x, float y, float z);
	// Rotation where t is given in angles
	void initialize_rotate_x(float t);
	void initialize_rotate_y(float t);
	void initialize_rotate_z(float t);
};

#endif