#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

class MyCamera
{
public:
	/// enum defining different camera modes
	enum CameraMode
	{
		NONE = 0,
		FIXED_LOOKING = 1, /// mode in which camera looks towards a point
		FORWARD_LOOKING = 2 /// mode in which camera always looks forward
	};

	/**
	* @brief We define MyCamera as a singleton class
	*		 API to return an instance of MyCamera class
	* @return MyCamera* - instance of MyCamera class
	*/
	static MyCamera* getInstance();

	/**
	* @brief destroys the instance of camera
	*/
	static void destroyInstance();

	/**
	* @brief API to set camera window
	* @param GLFWwindow* - camera window
	*/
	void setCameraWindow(GLFWwindow* window)
	{
		cameraWindow = window;
	}

	/**
	* @brief switches camera working mode
	* @param CameraMode - enum defining new camera mode
	*/
	void switchMode(CameraMode newMode);

	/**
	* @brief method to get view matrix of camera
	* @return const glm::mat4 - view matrix of camera
	*/
	const glm::mat4 getViewMatrix();

private:
	/// private constructor
	MyCamera();

	/// private destructor
	~MyCamera();

	/// process events
	void processEvent();

	static MyCamera* camera; //!< instance of MyCamera class
	glm::vec3 cameraPosition; //!< position of camera in world space
	glm::vec3 cameraTarget; //!< position of target towards which camera is pointing
	glm::vec3 cameraUpAxis; //!< vec3 defining up axis of camera
	CameraMode mode; //!< mode in which camera is working
	GLFWwindow* cameraWindow; //!< window in which camera is working
};

#endif