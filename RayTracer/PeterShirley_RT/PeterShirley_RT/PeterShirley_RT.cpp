// PeterShirley_RT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "fstream"

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"

using namespace std;

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

bool hitSphere(const glm::vec3& center, float radius, const Ray& ray)
{
	glm::vec3 OC = ray.origin() - center;
	float a = glm::dot(ray.direction(), ray.direction());
	float b = 2.*dot(OC, ray.direction());
	float c = glm::dot(OC, OC) - radius*radius;
	float determinant = b*b - 4 * a*c;
	return determinant > 0;
}

glm::vec3 getColor(const Ray& ray)
{
	if (hitSphere(glm::vec3(0, 0, -1), 0.1, ray))
		return glm::vec3(1.0, 0., 0.);

	glm::vec3 unitRay = glm::normalize(ray.direction());
	float t = 0.5 * (unitRay[1] + 1.);
	return (1.f - t)*glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 1200;
	int ny = 600;

	ofstream ofs("test.ppm", std::ofstream::out);

	ofs << "P3" << endl << nx << " " << ny << endl << 255 << endl;

	/// stub raytracing
	float progress = 0;

	glm::vec3 lowerLeft(-2.0, -1.0, -1.0);
	glm::vec3 origin(0, 0, 0);
	glm::vec3 hDirection(4., 0, 0);
	glm::vec3 vDirection(0, 2., 0);
	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < nx; j++)
		{
			float v = float(ny-1-i) / ny;
			float u = float(j) / nx;
			Ray sample(origin, lowerLeft + u*hDirection + v*vDirection);

			glm::vec3 color = getColor(sample);
			glm::vec3 RGBColor = float(255.99) * color;

			ofs << int(RGBColor[0]) << " " << int(RGBColor[1]) << " " << int(RGBColor[2]) << endl;
			progress = (float(i*nx + j) / (nx*ny));
		}

		printProgress(progress);
	}

	ofs.close();
}

