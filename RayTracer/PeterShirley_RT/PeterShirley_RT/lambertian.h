#ifndef LAMERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "utils.h"

class Lambertian : public Material
{
public:
	Lambertian(glm::vec3 a) : albedo(a) {};

	bool scatter(const Ray& rayIncoming, const HitRecord& hitRecord,
		glm::vec3& attenuation, Ray& rayScattered) const override
	{
		glm::vec3 targetDirection = hitRecord.p + hitRecord.normal + getRandomPointInUnitSphere();
		rayScattered = Ray(hitRecord.p, targetDirection - hitRecord.p);
		attenuation = albedo;
		return true;
	}

private:
	glm::vec3 albedo;
};

#endif