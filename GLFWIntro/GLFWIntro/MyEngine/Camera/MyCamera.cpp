#include "MyCamera.h"
#include "glm\gtc\matrix_transform.hpp"

#include "Utils\utils.h"
#include "Utils\globals.h"

/// definitions for MyCamera class

MyCamera* MyCamera::camera = NULL;

void MyCamera::destroyInstance()
{
	if (camera)
		delete camera;
}

MyCamera::MyCamera()
{
	cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraWindow = NULL;
}

MyCamera::~MyCamera()
{
	destroyInstance();
}

/// Definitions for MyFixedCamera class begins

MyCamera* MyFixedCamera::getInstance()
{
	if (camera == NULL)
	{
		camera = new MyFixedCamera();
	}
	else
	{
		MyFixedCamera* typeCamera = dynamic_cast<MyFixedCamera*>(camera);
		if (!typeCamera)
		{
			destroyInstance();
			camera = new MyFixedCamera();
		}
	}

	return camera;
}

MyFixedCamera::MyFixedCamera() : MyCamera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
}

MyFixedCamera::~MyFixedCamera()
{
	/// Nothing
}

const glm::mat4 MyFixedCamera::getViewMatrix()
{
	glm::mat4 viewMatrix;
	if (camera)
	{
		processEvent();
		viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUpAxis);
	}
	else
	{
		ERROR_LOG("ERROR::MYFIXEDCAMERA::GET_VIEWMATRIX", "Camera instance is NULL!");
	}

	return viewMatrix;
}

void MyFixedCamera::processEvent()
{
}