#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"
#include "material.h"

class Sphere : public Hitable
{
public:
	Sphere(){}

	Sphere(glm::vec3 center, float radius, Material* material)
	{
		C = center;
		R = radius;
		OMaterial = material;
	}

	~Sphere()
	{
		delete OMaterial;
	}

	bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const override
	{
		glm::vec3 RC = ray.origin() - C;
		float a = glm::dot(ray.direction(), ray.direction());
		float b = 2.f * glm::dot(ray.direction(), RC);
		float c = glm::dot(RC, RC) - R*R;
		float discriminant = b*b - 4 * a*c;
		float t;
		bool hitStatus = false;

		if (discriminant >= 0.)
		{
			t = (-b - glm::sqrt(discriminant)) / (2.*a);
			if (t > tMin && t < tMax)
			{
				hitStatus = true;
			}
			else
			{
				t = (-b + glm::sqrt(discriminant)) / (2.*a);
				if (t > tMin && t < tMax)
				{
					hitStatus = true;
				}
			}

			if(hitStatus)
			{
				rec.t = t;
				rec.p = ray.pointAtParameter(t);
				rec.normal = (rec.p - C) / R;
				rec.hMaterial = OMaterial;
			}
		}

		return hitStatus;
	}

private:
	glm::vec3 C;
	float R;
	Material* OMaterial;
};

#endif
