#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

/**
* @fn framebuffer_size_callback(GLFWwindow* window, int width, int height)
* @brief callback function for resize event
* @param GLFWwindow* - window on which callback event is called
* @param int - width of the window
* @param int - height of the window
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
* @fn processEvent(GLFWwindow* window)
* @brief callback function for processing window events
* @param GLFWwindow* - window on which callback events is called
*/
void processEvent(GLFWwindow* window);