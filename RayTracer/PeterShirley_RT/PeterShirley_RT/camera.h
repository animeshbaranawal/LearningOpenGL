#ifndef CAMERA_H
#define CAMERA_H

#include "glm.hpp"
#include "vec3.hpp"
#include "gtc\constants.hpp"

#include "ray.h"
#include "utils.h"

class Camera
{
public:
	Camera(glm::vec3 lookFrom = glm::vec3(0.,0.,0.), glm::vec3 lookAt = glm::vec3(0.,0.,-1.), 
		glm::vec3 vUp = glm::vec3(0.,1.,0.), float fOV = 2.f*glm::atan(50), float aspectRatio = 2,
		float aperture = 0, float focusRadius = 1.f)
	{
		lensRadius = aperture / 2;
		O = lookFrom;
		glm::vec3 w = glm::normalize(lookFrom - lookAt);
		glm::vec3 u = glm::normalize(glm::cross(vUp, w));
		glm::vec3 v = glm::cross(w, u);

		float fOVRadians = fOV*glm::pi<float>() / 180;
		float halfHeight = glm::tan(fOVRadians / 2);
		float halfWidth = aspectRatio*halfHeight;
		lowerLeft = O + focusRadius*(-halfWidth*u - halfHeight*v - w);
		hDir = 2 * halfWidth*focusRadius*u;
		vDir = 2 * halfHeight*focusRadius*v;
	}

	Ray getRay(float u, float v) const
	{
		glm::vec3 rX = lensRadius*getRandomPointInUnitDisk();
		glm::vec3 offset = hDir*rX.x + vDir*rX.y;
		return Ray(O + offset, lowerLeft + u*hDir + v*vDir - O - offset);
	}

private:
	glm::vec3 lowerLeft;
	glm::vec3 hDir;
	glm::vec3 vDir;
	glm::vec3 O;
	float lensRadius;
};

#endif