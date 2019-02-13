#ifndef MATERIAL_H
#define MATERIAL_H

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"
#include "hitable.h"

class Material
{
public:
	virtual bool scatter(const Ray& rayIncoming, const HitRecord& hitRecord,
		glm::vec3& attenuation, Ray& rayScattered) const = 0;
};

#endif