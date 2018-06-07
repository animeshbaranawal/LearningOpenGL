#include "MyShader.h"
#include "utils.h"

MyShader::MyShader()
{
	shaderID = 0;
	shaderData = NULL;
	shaderType = MyShaderType::None;
}

MyShader::~MyShader()
{
	if (!shaderID)
	{
		glDeleteShader(shaderID);
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADER::DELETION_FAILED", "Could not shader with 0 ID!");
	}
}

void MyShader::readShaderFromString(std::string shaderSource)
{
	shaderData = new char[shaderSource.length()];
	strcpy_s(shaderData, shaderSource.length(), shaderSource.c_str());
}

void MyShader::readShaderFromFile(std::string shaderSourceFile)
{
	readFile(shaderSourceFile.c_str(), &shaderData);
}

bool MyShader::setShaderTypeAsVertex()
{
	bool success = false;
	if (shaderType == MyShaderType::None)
	{
		shaderType = MyShaderType::Vertex;
		success = true;
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADER::SET_VERTEXTYPE_FAILED", "Shader type has already been set!");
	}
	return success;
}

bool MyShader::setShaderTypeAsFragment()
{
	bool success = false;
	if (shaderType == MyShaderType::None)
	{
		shaderType = MyShaderType::Fragment;
		success = true;
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADER::SET_FRAGMENTTYPE_FAILED", "Shader type has already been set!");
	}
	return success;
}

bool MyShader::compileShader()
{
	bool success = false;
	if (!shaderID)
	{
		if (shaderType == MyShader::None)
		{
			return success;
		}
		shaderID = glCreateShader(shaderType);
		glShaderSource(shaderID, 1, &shaderData, NULL);
		glCompileShader(shaderID);
		success = true;
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADER::COMPILATION_FAILED", "Cannot re-compile a shader");
	}

	return success;
}

void MyShader::getShaderCompilationStatus(int& success, char** logMessage, unsigned int logLength)
{
	if (shaderID != 0)
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			if (*logMessage) delete (*logMessage);
			*logMessage = new char[logLength];

			glGetShaderInfoLog(shaderID, logLength, NULL, *logMessage);
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADER::GET_COMPILATION_STATUS_FAILED", 
			"Cannot get compilation status of 0 ID shader!");
	}
}