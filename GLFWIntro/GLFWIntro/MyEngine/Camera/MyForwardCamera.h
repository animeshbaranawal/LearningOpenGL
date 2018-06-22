#ifndef MYFORWARDCAMERA_H
#define MYFORWARDCAMERA_H

#include "MyCamera.h"

class MyForwardCamera : public MyCamera
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

	virtual void processMouseEvent(GLFWwindow* window, double xpos, double ypos) {}

	virtual void processScrollEvent(GLFWwindow* window, double xOffset, double yOffset) {}

protected:
	MyForwardCamera();

	virtual ~MyForwardCamera();

	virtual void processEvent();
};

#endif
