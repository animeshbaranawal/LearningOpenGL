#include "MyShaderProgram.h"
#include "MyShader.h"
#include "utils.h"

MyShaderProgram::MyShaderProgram(const MyShader* myVertexShader, const MyShader* myFragmentShader)
{
	vertexShader = myVertexShader;
	fragmentShader = myFragmentShader;
	ID = 0;
}

bool MyShaderProgram::linkShaderProgram()
{
	MyShader::MyShaderType vertexShaderType = MyShader::None;
	MyShader::MyShaderType fragmentShaderType = MyShader::None;

	if (vertexShader &&  vertexShader->getShaderID())
		vertexShaderType = vertexShader->getShaderType();
	else
		ERROR_LOG("ERROR::MYSHADERPROGRAM::LINKING_FAILED", "Vertex shader has not been set properly");

	if (fragmentShader && fragmentShader->getShaderID())
		fragmentShaderType = fragmentShader->getShaderType();
	else
		ERROR_LOG("ERROR::MYSHADERPROGRAM::LINKING_FAILED", "Fragment shader has not been set properly");

	bool success = false;
	if (!ID)
	{
		if (vertexShaderType == GL_VERTEX_SHADER && fragmentShaderType == GL_FRAGMENT_SHADER)
		{
			ID = glCreateProgram();
			glAttachShader(ID, vertexShader->getShaderID());
			glAttachShader(ID, fragmentShader->getShaderID());
			glLinkProgram(ID);
			success = true;
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADERPROGRAM::LINKING_FAILED", "Cannot relink a shader program!");
	}

	return success;
}

void MyShaderProgram::getShaderLinkingStatus(int& linkingSuccess, char** logMessage, unsigned int logLength)
{
	if (ID != 0)
	{
		glGetProgramiv(ID, GL_LINK_STATUS, &linkingSuccess);
		if (!linkingSuccess)
		{
			if (*logMessage != NULL) delete *logMessage;
			*logMessage = new char[logLength];

			glGetProgramInfoLog(ID, logLength, NULL, *logMessage);
		}
	}
	else
	{
		ERROR_LOG("ERROR::MYSHADERPROGRAM::GET_LINKING_STATUS_FAILED",
			"Cannot get linking status of a 0 ID shader program!");
	}
}

void MyShaderProgram::use()
{
	if (ID != 0)
		glUseProgram(ID);
	else
		ERROR_LOG("ERROR::MYSHADERPROGRAM::USE_FAILED", "Cannot use a 0 ID shader program!");
}