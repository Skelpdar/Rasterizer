#include "Camera.h"

/**
Returns the camera translation matrix
*/
Matrix4 Camera::getTranslationMatrix() {
	Matrix4 m;
	m.initialize_translation(-position.matrix[0], -position.matrix[1], -position.matrix[2]);
	return m;
}

/**
Returns the camera rotation matrix around the x-axis
*/
Matrix4 Camera::getXRotationMatrix() {
	Matrix4 m;
	m.initialize_rotate_x(-rotation.matrix[0]);
	return m;
}

/**
Returns the camera rotation matrix around the y-axis
*/
Matrix4 Camera::getYRotationMatrix() {
	Matrix4 m;
	m.initialize_rotate_y(-rotation.matrix[1]);
	return m;
}

/**
Returns the camera rotation matrix around the z-axis
*/
Matrix4 Camera::getZRotationMatrix() {
	Matrix4 m;
	m.initialize_rotate_z(-rotation.matrix[2]);
	return m;
}