#ifndef CAMERA_H
#define CAMERA_H

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"

class Camera
{
public:
	Camera()
	{
		lowerLeft = glm::vec3(-2., -1., -1.);
		hDir = glm::vec3(4., 0., 0.);
		vDir = glm::vec3(0., 2., 0.);
		O = glm::vec3(0., 0., 0.);
	}

	Ray getRay(float u, float v) const
	{
		return Ray(O, lowerLeft + u*hDir + v*vDir - O);
	}

private:
	glm::vec3 lowerLeft;
	glm::vec3 hDir;
	glm::vec3 vDir;
	glm::vec3 O;

};

#endif