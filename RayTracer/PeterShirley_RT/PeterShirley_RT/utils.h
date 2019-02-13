#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#include "glm.hpp"
#include "vec3.hpp"

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

#endif