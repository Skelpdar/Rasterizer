#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"

class Camera {
public:
	Matrix position;
	Matrix rotation;

	Matrix4 getXRotationMatrix();
	Matrix4 getYRotationMatrix();
	Matrix4 getZRotationMatrix();
	Matrix4 getTranslationMatrix();
};

#endif