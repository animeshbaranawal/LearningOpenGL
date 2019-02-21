// PeterShirley_RT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include "fstream"
#include "float.h"
#include <cstdlib>
#include <vector>

#include "glm.hpp"
#include "vec3.hpp"

#include "ray.h"
#include "hitableList.h"
#include "sphere.h"
#include "camera.h"
#include "utils.h"
#include "metal.h"
#include "lamertian.h"
#include "dielectric.h"

using namespace std;
#define SAMPLING 50
#define DEPTHLEVEL 50
#define WEIGHTED_AVERAGE 1
#define ALPHA 2./(SAMPLING+1)

glm::vec3 getColor(const Ray& ray, Hitable* world, int depth)
{
	HitRecord worldHit;
	if (world->hit(ray, 0.001, FLT_MAX, worldHit) && depth < DEPTHLEVEL)
	{
		Ray scatteredRay;
		glm::vec3 attenuation;
		if (worldHit.hMaterial->scatter(ray, worldHit, attenuation, scatteredRay))
		{
			return (1.0f - attenuation) * getColor(scatteredRay, world, depth+1);
		}
		else
		{
			/// cout << "HIT" << endl;
			return glm::vec3(0., 0., 0.);
		}
	}

	glm::vec3 unitRay = glm::normalize(ray.direction());
	float t = 0.5 * (unitRay[1] + 1.);
	return (1.f - t)*glm::vec3(1, 1, 1) + t * glm::vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 200;
	int ny = 100;

	/// create world
	Camera worldCamera;
	Hitable* spheres[4];
	spheres[0] = new Sphere(glm::vec3(0, 0, -1), 0.5, new Lambertian(glm::vec3(0.2,0.7,0.7)));
	spheres[1] = new Sphere(glm::vec3(0, -100.5, -1), 100, new Lambertian(glm::vec3(0.2,0.2,1.0)));
	spheres[2] = new Sphere(glm::vec3(1, 0, -1), 0.5, new Metal(glm::vec3(0.2, 0.4, 0.8), 0.3));
	spheres[3] = new Sphere(glm::vec3(-1, 0, -1), 0.5, new Dielectric(1.5));
	
	Hitable* world = new HitableList(spheres, 4);

	/// init color values;
	vector< vector<glm::vec3> > pixels(ny);
	for (int i = 0; i < ny; i++)
	{
		pixels[i].resize(nx);
		for (int j = 0; j < nx; j++)
		{
			pixels[i][j] = glm::vec3(0., 0., 0.);
		}
	}

	string fileName = "test5.ppm";
	ofstream ofs(fileName, std::ofstream::out);
	ofs << "P3" << endl << nx << " " << ny << endl << 255 << endl;

	/// run
	for (int k = 0; k < SAMPLING; k++)
	{
		/*string fileName = "test_movingAverage";
		char iter[(sizeof(int) * 8 + 1)];
		_itoa_s(k, iter, (sizeof(int) * 8 + 1), 10);
		float alpha = 2.f/(SAMPLING+1);

		ofstream ofs(fileName + iter + ".ppm", std::ofstream::out);
		ofs << "P3" << endl << nx << " " << ny << endl << 255 << endl;*/

		/// stub raytracing
		float progress = 0;

		for (int i = 0; i < ny; i++)
		{
			for (int j = 0; j < nx; j++)
			{
				float dv = float(rand()) / float(RAND_MAX);
				float du = float(rand()) / float(RAND_MAX);
				float v = float(ny - 1 - i + dv) / ny;
				float u = float(j + du) / nx;

				Ray sample = worldCamera.getRay(u, v);

				if (!WEIGHTED_AVERAGE)
				{
					pixels[i][j] = (pixels[i][j] == glm::vec3(0., 0., 0.)) ?
						getColor(sample, world, 0) :
						(float(1.0f - ALPHA)*pixels[i][j] + float(ALPHA)*getColor(sample, world, 0)); /// running average
				}
				else
				{
					pixels[i][j] = pixels[i][j] * (float(k) / float(k + 1)) + getColor(sample, world, 0)*1.f / float(k + 1);
				}
					

				/*glm::vec3 RGBColor = float(255.99) * glm::sqrt(pixels[i][j]);
				ofs << int(RGBColor[0]) << " " << int(RGBColor[1]) << " " << int(RGBColor[2]) << endl;*/
				
				progress = (float(k*nx*ny + i*nx + j) / (SAMPLING*nx*ny));
				printProgress(progress);
			}
		}

		/// ofs.close();
	}

	/// write to file
	for (int i = 0; i < ny; i++)
	{
		for (int j = 0; j < nx; j++)
		{
			glm::vec3 RGBColor = float(255.99) * glm::sqrt(pixels[i][j]);
			ofs << int(RGBColor[0]) << " " << int(RGBColor[1]) << " " << int(RGBColor[2]) << endl;
		}
	}

	ofs.close();
}

