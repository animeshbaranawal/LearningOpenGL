#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <string>

class MyShader
{
private:
	/// enum specifying types of shaders
	enum MyShaderType
	{
		None = -1,
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};

public:	
	/**
	* @brief constructor
	*/
	MyShader();

	/**
	* @brief destructor
	*		 Deletes the associated shader before destroying object
	*/
	~MyShader();

	/**
	* @brief method to compile a shader
	* @return bool - returns true if glCompileShader() was successfully called
	*/
	bool compileShader();

	/**
	* @brief method to read shader from a string
	* @param std::string - string from which shader is to be read
	*/
	void readShaderFromString(std::string shaderSource);

	/**
	* @brief method to read shader from a source file
	* @param std::string - path of the source file
	*/
	void readShaderFromFile(std::string shaderSourceFile);
	
	/**
	* @brief sets the shader type to vertex if shader type not set
	* @return bool - shader type successfully set
	*/
	bool setShaderTypeAsVertex();

	/**
	* @brief sets the shader type to fragment if shader type not set
	* @return bool - shader type successfully set
	*/
	bool setShaderTypeAsFragment();

	/**
	* @brief method to get shader compilation status
	* @param int& - compilation status of shader, 0 if successful
	* @param char** - log message for shader compilation
	* @param unsigned int - length of the log message to acquire
	*/
	void getShaderCompilationStatus(int& compilationStatus, char** logMessage, unsigned int logLength);

	/**
	* @brief method to get the shader ID
	* @return const unsigned int - id allotted to the shader
	*/
	const unsigned int getShaderID() const
	{
		return shaderID;
	}

private:
	unsigned int shaderID; //!< unique id of shader in OpenGL
	char* shaderData; //!< string denoting program of the shader
	MyShaderType shaderType; //!< type of shader
};