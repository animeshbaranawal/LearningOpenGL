#ifndef METAL_H
#define METAL_H

#include <algorithm>

#include "material.h"
#include "utils.h"

class Metal : public Material
{
public:
	Metal(glm::vec3 a, float r) : albedo(a) 
	{
		fuzzballRadius = std::min(1.f, r);
	}

	bool scatter(const Ray& rayIncoming, const HitRecord& hitRecord,
		glm::vec3& attenuation, Ray& rayScattered) const override
	{
		glm::vec3 targetRayDirection = glm::reflect(rayIncoming.direction(), hitRecord.normal);
		targetRayDirection += fuzzballRadius * getRandomPointInUnitSphere();

		rayScattered = Ray(hitRecord.p, targetRayDirection);
		attenuation = albedo;
		return glm::dot(hitRecord.normal, rayScattered.direction()) > 0.;
	}

private:
	glm::vec3 albedo;
	float fuzzballRadius;
};

#endif