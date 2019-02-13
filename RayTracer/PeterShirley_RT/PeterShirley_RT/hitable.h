#ifndef HITABLE_H
#define HITABLE_H

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"

class Material;

struct HitRecord
{
	float t;
	glm::vec3 p;
	glm::vec3 normal;
	Material* hMaterial;
};

class Hitable
{
public:
	virtual bool hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) const = 0;
};

#endif