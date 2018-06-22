#ifndef MYCAMERA_H
#define MYCAMERA_H

#include "glad\glad.h"
#include "GLFW\glfw3.h"
#include "glm\glm.hpp"

class MyCamera
{
public:
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
	* @brief method to get view matrix of camera
	* @return const glm::mat4 - view matrix of camera
	*/
	virtual const glm::mat4 getViewMatrix() = 0;

	/// Callback functions for processing mouse events in camera
	virtual void processMouseEvent(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void processScrollEvent(GLFWwindow* window, double xOffset, double yOffset) = 0;

protected:
	/// private constructor
	MyCamera();

	/// private destructor
	virtual ~MyCamera();

	/// process keyboard events
	virtual void processEvent() = 0;

	static MyCamera* camera; //!< instance of MyCamera class
	glm::vec3 cameraPosition; //!< position of camera in world space
	glm::vec3 cameraTarget; //!< position of target towards which camera is pointing
	glm::vec3 cameraUpAxis; //!< vec3 defining up axis of camera
	
	GLFWwindow* cameraWindow; //!< window in which camera is working
};

class MyFixedCamera : public MyCamera 
{
public:
	/**
	* @brief We define MyCamera as a singleton class
	*		 API to return an instance of MyCamera class
	* @return MyCamera* - instance of MyCamera class
	*/
	static MyCamera* getInstance();

	/**
	* @brief method to get view matrix of camera
	* @return const glm::mat4 - view matrix of camera
	*/
	virtual const glm::mat4 getViewMatrix();

	virtual void processMouseEvent(GLFWwindow* window, double xpos, double ypos){}

	virtual void processScrollEvent(GLFWwindow* window, double xOffset, double yOffset) {}

protected:
	MyFixedCamera();

	virtual ~MyFixedCamera();

	virtual void processEvent();

	struct Function
	{
		void operator()(int a) {}
	};
};

#endif