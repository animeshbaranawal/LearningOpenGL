#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "glm.hpp"
#include "vec3.hpp"

#include "material.h"
#include "utils.h"

class Dielectric : public Material
{
public:
	Dielectric(float ri) : refractiveIndex(ri) {}

	bool scatter(const Ray& rayIncoming, const HitRecord& hitRecord,
		glm::vec3& attenuation, Ray& rayScattered) const override
	{
		attenuation = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 outwardNormal = glm::dot(rayIncoming.direction(), hitRecord.normal) > 0 ?
									-hitRecord.normal :
									hitRecord.normal;
		float n_over_nt = glm::dot(rayIncoming.direction(), hitRecord.normal) > 0 ?
							refractiveIndex :
							1.f/refractiveIndex;

		glm::vec3 reflectedDir = glm::reflect(rayIncoming.direction(), outwardNormal);
		glm::vec3 refractDir;
		
		if (refract(glm::normalize(rayIncoming.direction()), outwardNormal, refractDir, n_over_nt))
		{
			rayScattered = Ray(hitRecord.p, refractDir);
		}
		else
		{
			rayScattered = Ray(hitRecord.p, reflectedDir);
			/// return false;
		}

		return true;
	}

private:
	float refractiveIndex;
};

#endif