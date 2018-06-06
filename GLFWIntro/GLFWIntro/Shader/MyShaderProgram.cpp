#include "MyShaderProgram.h"
#include "MyShader.h"

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

	if (vertexShader)
		vertexShaderType = vertexShader->getShaderType();
	if (fragmentShader)
		fragmentShaderType = fragmentShader->getShaderType();

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
}

void MyShaderProgram::use()
{
	if(ID != 0)
		glUseProgram(ID);
}