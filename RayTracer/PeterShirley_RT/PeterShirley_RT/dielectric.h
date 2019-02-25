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
		float reflectProb;
		float cosine = glm::dot(rayIncoming.direction(), hitRecord.normal) / glm::length(rayIncoming.direction());
		
		attenuation = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 outwardNormal;
		float n_over_nt;

		if (glm::dot(rayIncoming.direction(), hitRecord.normal) > 0)
		{
			outwardNormal = -hitRecord.normal;
			n_over_nt = refractiveIndex;
			cosine = refractiveIndex*cosine;
		}
		else
		{
			outwardNormal = hitRecord.normal;
			n_over_nt = 1. / refractiveIndex;
			cosine = -cosine;
		}

		glm::vec3 refractDir;		
		glm::vec3 reflectedDir = glm::reflect(rayIncoming.direction(), outwardNormal);
		
		if (refract(glm::normalize(rayIncoming.direction()), outwardNormal, refractDir, n_over_nt))
		{
			reflectProb = schlick(cosine, refractiveIndex);
		}
		else
		{
			reflectProb = 1.;
		}

		if (getRandomNormalPoint() < reflectProb)
		{
			rayScattered = Ray(hitRecord.p, reflectedDir);
		}
		else
		{
			rayScattered = Ray(hitRecord.p, refractDir);
		}

		return true;
	}

private:
	float refractiveIndex;
};

#endif