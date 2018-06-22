#include "MyEulerCamera.h"
#include "glm\gtc\matrix_transform.hpp"

#include "Utils\utils.h"
#include "Utils\globals.h"

MyCamera* MyEulerCamera::getInstance()
{
	if (camera == NULL)
	{
		camera = new MyEulerCamera();
	}
	else
	{
		MyEulerCamera* typeCamera = dynamic_cast<MyEulerCamera*>(camera);
		if (!typeCamera)
		{
			destroyInstance();
			camera = new MyEulerCamera();
		}
	}

	return camera;
}

const glm::mat4 MyEulerCamera::getViewMatrix()
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

void MyEulerCamera::processEvent()
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

void MyEulerCamera::processMouseEvent(GLFWwindow* window, double xPos, double yPos)
{
	if (cameraWindow && window == cameraWindow)
	{
		if (firstTime)
		{
			last_X = xPos;
			last_Y = yPos;
			firstTime = false;
		}

		float xoffset = xPos - last_X;
		float yoffset = last_Y - yPos;
		last_X = xPos;
		last_Y = yPos;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraTarget = glm::normalize(front);
	}
	else
	{
		ERROR_LOG("ERROR::MYEULERCAMERA::PROCESS_MOUSEEVENT", "Camera window not set properly!");
	}
}

void MyEulerCamera::processScrollEvent(GLFWwindow* window, double xOffset, double yOffset)
{
	if (cameraWindow && cameraWindow == window)
	{
		if (fov >= 1.0f && fov <= 45.0f)
			fov -= yOffset;
		if (fov <= 1.0f)
			fov = 1.0f;
		if (fov >= 45.0f)
			fov = 45.0f;
	}
	else
	{
		ERROR_LOG("ERROR::MYEULERCAMERA::PROCESS_SCROLLEVENT", "Camera window not set properly!");
	}
}

MyEulerCamera::MyEulerCamera() : MyCamera()
{
	cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraTarget = glm::vec3(0.0f, 0.0f, -1.0f);

	yaw = 0.0f;
	pitch = 0.0f;
	fov = 45.0f;
	firstTime = true;
}

MyEulerCamera::~MyEulerCamera()
{
	/// do nothing
}
