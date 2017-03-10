#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iterator>
#include <iostream>
#include <cmath>
#include <memory>
#include "Eigen/Core"


#define PI 3.14159265

	// 4x1 matrix for vertex position data
	class Matrix {
	public:
		std::vector<float> matrix;
		Matrix();
		Matrix(float x, float y, float z);
	};

	// The 4x4 transformation matrices
	class Matrix4 {
		void array_to_matrix(float* a);

	public:
		//Outer vector is columns, inner is the rows
		std::vector< std::vector<float> > matrix;

		Matrix mult(Matrix m);
		Matrix4 mult(Matrix4 m);

		void initialize_identity();
		void initialize_translation(float x, float y, float z);
		void initialize_scaling(float x, float y, float z);

		// Rotation where t is given in angles
		void initialize_rotate_x(float t);
		void initialize_rotate_y(float t);
		void initialize_rotate_z(float t);
	};

	Eigen::Matrix4f translation(float x, float y, float z);
	Eigen::Matrix4f scale(float x, float y, float z);
	Eigen::Matrix4f rotatex(float t);
	Eigen::Matrix4f rotatey(float t);
	Eigen::Matrix4f rotatez(float t);



#endif