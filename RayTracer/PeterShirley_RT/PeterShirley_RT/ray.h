#ifndef RAY_H
#define RAY_H

#include "glm.hpp"
#include "vec3.hpp"

class Ray
{
public:
	Ray() {}
	
	Ray(glm::vec3 Origin, glm::vec3 Direction)
	{
		A = Origin;
		B = Direction;
	}

	glm::vec3 origin() const { return A; }
	glm::vec3 direction() const { return B; }
	glm::vec3 pointAtParameter(double t) const
	{
		glm::vec1 parameter(t);
		return A + parameter*B;
	}

	glm::vec3 A;
	glm::vec3 B;
};

#endif
