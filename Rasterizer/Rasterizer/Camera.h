#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix.h"
#include "Eigen/Core"
#include "Eigen/Geometry"
#include <cmath>

class Camera {
public:
	Eigen::Vector4f position;
	Eigen::Vector4f rotation;

	Eigen::Matrix4f getXRotationMatrix();
	Eigen::Matrix4f getYRotationMatrix();
	Eigen::Matrix4f getZRotationMatrix();
	Eigen::Matrix4f getTranslationMatrix();
};

#endif