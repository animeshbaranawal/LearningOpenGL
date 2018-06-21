#include "MyCamera.h"
#include "glm\gtc\matrix_transform.hpp"

#include "Utils\utils.h"
#include "Utils\globals.h"

MyCamera* MyCamera::camera = NULL;

MyCamera* MyCamera::getInstance()
{
	if (camera == NULL)
	{
		camera = new MyCamera();
	}

	return camera;
}

void MyCamera::destroyInstance()
{
	if (camera)
		delete camera;
}

void MyCamera::switchMode(CameraMode newMode)
{
	if (newMode != mode)
	{
		mode = newMode;
	}
}

const glm::mat4 MyCamera::getViewMatrix()
{
	glm::mat4 viewMatrix;
	if (camera)
	{
		processEvent();
		switch (mode)
		{
		case FIXED_LOOKING:
			viewMatrix = glm::lookAt(cameraPosition, cameraTarget, cameraUpAxis);
			break;

		case FORWARD_LOOKING:
			viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraTarget, cameraUpAxis);
			break;

		default:
			break;
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYCAMERA::GET_VIEWMATRIX", "Camera instance is NULL!");
	}

	return viewMatrix;
}

MyCamera::MyCamera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUpAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	mode = CameraMode::FIXED_LOOKING;
	cameraWindow = NULL;
}

MyCamera::~MyCamera()
{
	destroyInstance();
}

void MyCamera::processEvent()
{
	if (cameraWindow)
	{
		float cameraSpeed = 2.5 * delta_time;
		if (glfwGetKey(cameraWindow, GLFW_KEY_W) == GLFW_PRESS)
		{
			cameraPosition += cameraSpeed * cameraTarget;
		}
		if (glfwGetKey(cameraWindow, GLFW_KEY_S) == GLFW_PRESS)
		{
			cameraPosition -= cameraSpeed * cameraTarget;
		}
		if (glfwGetKey(cameraWindow, GLFW_KEY_A) == GLFW_PRESS)
		{
			cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraUpAxis, cameraTarget));
		}
		if (glfwGetKey(cameraWindow, GLFW_KEY_D) == GLFW_PRESS)
		{
			cameraPosition += cameraSpeed * glm::normalize(glm::cross(cameraTarget, cameraUpAxis));
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYCAMERA::EVENTPROCESS_FAILED", "No camera window present!");
	}
}