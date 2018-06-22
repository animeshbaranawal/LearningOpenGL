#ifndef MYEULERCAMERA_H
#define MYEULERCAMERA_H

#include "MyCamera.h"

class MyEulerCamera : public MyCamera
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

	virtual void processMouseEvent(GLFWwindow* window, double xpos, double ypos);

	virtual void processScrollEvent(GLFWwindow* window, double xOffset, double yOffset);

protected:
	MyEulerCamera();

	virtual ~MyEulerCamera();

	virtual void processEvent();

private:
	float yaw; //!< yaw of the camera
	float pitch; //!< pitch of the camera
	float fov; //!< field of view of the camera
	bool firstTime; //!< the first time mouse event is processed by camera
};

#endif
