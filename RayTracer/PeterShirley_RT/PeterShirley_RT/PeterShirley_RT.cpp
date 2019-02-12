// PeterShirley_RT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "float.h"

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"

using namespace std;
#define SAMPLING 100

/// see : https://stackoverflow.com/questions/14539867/how-to-display-a-progress-indicator-in-pure-c-c-cout-printf
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage)
{
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

glm::vec3 getRandomPointInUnitSphere()
{
	float dx, dy, dz;
	glm::vec3 rPoint;
	do
	{
		dx = float(rand()) / float(RAND_MAX);
		dy = float(rand()) / float(RAND_MAX);
		dz = float(rand()) / float(RAND_MAX);
		rPoint = 2.f*glm::vec3(dx, dy, dz);

	} while (glm::length(rPoint) >= 1.);

	return rPoint;
}

glm::vec3 getColor(const Ray& ray, Hitable* world)
{
	HitRecord worldHit;
	if (world->hit(ray, 0.001, FLT_MAX, worldHit))
	{
		Ray scatteredRay(worldHit.p, worldHit.normal + getRandomPointInUnitSphere());
		return 0.5f * getColor(scatteredRay, world);
	}

	glm::vec3 unitRay = glm::normalize(ray.direction());
	float t = 0.5 * (unitRay[1] + 1.);
	return (1.f - t)*glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 400;
	int ny = 200;

	ofstream ofs("test2.ppm", std::ofstream::out);

	ofs << "P3" << endl << nx << " " << ny << endl << 255 << endl;

	/// create world
	Camera worldCamera;
	Hitable* spheres[2];
	spheres[0] = new Sphere(glm::vec3(0, 0, -1), 0.5);
	spheres[1] = new Sphere(glm::vec3(0, -100.5, -1), 100);
	Hitable* world = new HitableList(spheres, 2);

	/// stub raytracing
	float progress = 0;

	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < nx; j++)
		{
			glm::vec3 color = glm::vec3(0,0,0);
			for (int k = 0; k < SAMPLING; k++)
			{
				float dv = float(rand()) / float(RAND_MAX);
				float du = float(rand()) / float(RAND_MAX);
				float v = float(ny - 1 - i + dv) / ny;
				float u = float(j + du) / nx;
				
				Ray sample = worldCamera.getRay(u, v);
				color = (color*float(k) + getColor(sample, world))/float(k+1); /// running average
			}

			glm::vec3 RGBColor = float(255.99) * glm::sqrt(color);
			ofs << int(RGBColor[0]) << " " << int(RGBColor[1]) << " " << int(RGBColor[2]) << endl;
			progress = (float(i*nx + j) / (nx*ny));
		}

		printProgress(progress);
	}

	ofs.close();
}

