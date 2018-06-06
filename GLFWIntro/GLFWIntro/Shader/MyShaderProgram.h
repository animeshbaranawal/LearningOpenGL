#ifndef MYSHADERPROGRAM_H
#define MYSHADERPROGRAM_H

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <iostream>

/// forward declaration
class MyShader;

class MyShaderProgram
{
public:
	/**
	* @brief constructor
	* @param const MyShader* - vertex Shader class object
	* @param const MyShader* - fragment Shader class object
	*/
	MyShaderProgram(const MyShader* vertexShader, const MyShader* fragmentShader);
	
	/**
	* @brief method to link the shader program
	* @return bool - returns true if glLinkProgram() was called
	*/
	bool linkShaderProgram();

	/**
	* @brief method to get shader program linking status
	* @param int& - linking status of shader, 0 if not successful
	* @param char** - log message for shader compilation
	* @param unsigned int - length of the log message to acquire
	*/
	void getShaderLinkingStatus(int& linkingStatus, char** logMessage, unsigned int logLength);

	/**
	* @brief start using the given shader program
	*/
	void use();
	
	/**
	* @brief method to get the program ID
	* @return const unsigned int - program ID assigned by OpenGL
	*/
	const unsigned int getProgramID() const
	{
		return ID;
	}

	//// utility uniform functions
	//void setBool(const std::string &name, bool value) const;
	//void setInt(const std::string &name, int value) const;
	//void setFloat(const std::string &name, float value) const;

private:
	unsigned int ID; //!< unique ID assigned to shaderProgram by OpenGL
	const MyShader* vertexShader; //!< vertex shader component of the program
	const MyShader* fragmentShader; //!< fragment shader component of the program
};

#endif