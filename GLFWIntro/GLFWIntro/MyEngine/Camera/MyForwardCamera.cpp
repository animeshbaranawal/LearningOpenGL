#include "MyForwardCamera.h"
#include "glm\gtc\matrix_transform.hpp"

#include "Utils\utils.h"
#include "Utils\globals.h"

MyCamera* MyForwardCamera::getInstance()
{
	if (camera == NULL)
	{
		camera = new MyForwardCamera();
	}
	else
	{
		MyForwardCamera* typeCamera = dynamic_cast<MyForwardCamera*>(camera);
		if (!typeCamera)
		{
			destroyInstance();
			camera = new MyForwardCamera();
		}
	}

	return camera;
}

const glm::mat4 MyForwardCamera::getViewMatrix()
{
	glm::mat4 viewMatrix;
	if (camera)
	{
		processEvent();
		viewMatrix = glm::lookAt(cameraPosition, cameraPosition + cameraTarget, cameraUpAxis);
	}
	else
	{
		ERROR_LOG("ERROR::MYFORWARDCAMERA::GET_VIEWMATRIX", "Camera instance is NULL!");
	}

	return viewMatrix;
}

void MyForwardCamera::processEvent()
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

MyForwardCamera::MyForwardCamera() : MyCamera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);
}

MyForwardCamera::~MyForwardCamera()
{
	/// do nothing
}