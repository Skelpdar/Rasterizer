#include "Camera.h"

/**
Returns the camera translation matrix
*/
Eigen::Matrix4f Camera::getTranslationMatrix() {
	Eigen::Matrix4f m;
	//m.initialize_translation(-position.matrix[0], -position.matrix[1], -position.matrix[2]);

	m << 1, 0, 0, -position(0, 0),
		0, 1, 0, -position(1, 0),
		0, 0, 1, -position(2, 0),
		0, 0, 0, 1;

	return m;
}

/**
Returns the camera rotation matrix around the x-axis
*/
Eigen::Matrix4f Camera::getXRotationMatrix() {
	Eigen::Matrix4f m;
	//m.initialize_rotate_x(-rotation.matrix[0]);
	float r = -rotation(0, 0) * PI / 180;
	m << 1, 0, 0, 0,
		0, cos(r), -sin(r), 0,
		0, sin(r), cos(r), 0,
		0, 0, 0, 1;

	return m;
}

/**
Returns the camera rotation matrix around the y-axis
*/
Eigen::Matrix4f Camera::getYRotationMatrix() {
	Eigen::Matrix4f m;
	//m.initialize_rotate_y(-rotation.matrix[1]);
	float r = -rotation(1, 0) * PI / 180;
	m << cos(r), 0, sin(r), 0,
		0, 1, 0, 0,
		-sin(r), 0, cos(r), 0,
		0, 0, 0, 1;

	return m;
}

/**
Returns the camera rotation matrix around the z-axis
*/
Eigen::Matrix4f Camera::getZRotationMatrix() {
	Eigen::Matrix4f m;
	//m.initialize_rotate_z(-rotation.matrix[2]);
	float r = -rotation(2, 0) * PI / 180;
	m << cos(r), -sin(r), 0, 0,
		sin(r), cos(r), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1;

	return m;
}