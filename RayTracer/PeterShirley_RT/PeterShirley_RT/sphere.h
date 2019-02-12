#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere : public Hitable
{
public:
	Sphere(){}

	Sphere(glm::vec3 center, float radius)
	{
		C = center;
		R = radius;
	}

	bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override
	{
		glm::vec3 RC = ray.origin() - C;
		float a = glm::dot(ray.direction(), ray.direction());
		float b = 2.f * glm::dot(ray.direction(), RC);
		float c = glm::dot(RC, RC) - R*R;
		float discriminant = b*b - 4 * a*c;
		float t;

		if (discriminant >= 0.)
		{
			t = (-b - glm::sqrt(discriminant)) / (2.*a);
			if (t > tMin && t < tMax)
			{
				rec.t = t;
				rec.p = ray.pointAtParameter(t);
				rec.normal = glm::normalize(rec.p - C);
				return true;
			}
		
			t = (-b + glm::sqrt(discriminant)) / (2.*a);
			if (t > tMin && t < tMax)
			{
				rec.t = t;
				rec.p = ray.pointAtParameter(t);
				rec.normal = glm::normalize(rec.p - C);
				return true;
			}
		}

		return false;
	}

private:
	glm::vec3 C;
	float R;
};

#endif
