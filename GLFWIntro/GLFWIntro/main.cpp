#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <iostream>

#include "Shader\MyShader.h"
#include "Shader\MyShaderProgram.h"
#include "Callback\callback_functions.h"
#include "utils.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/// creating a new window for OpenGL
	GLFWwindow* window = glfwCreateWindow(400, 400, "Learning OpenGL", NULL, NULL);
	if (window == NULL)
	{
		ERROR_LOG("ERROR::GLFW", "Could not create window!");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		ERROR_LOG("ERROR::GLAD", "Could not initialise glad!");
		return -1;
	}

	glViewport(0, 0, 400, 400);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	float verticesAndColors[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	/// create a data buffer and copy data
	unsigned int VBO_points;
	glGenBuffers(1, &VBO_points);

	unsigned int VBO_colors;
	glGenBuffers(1, &VBO_colors);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	/// creata vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColors), verticesAndColors, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0));
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColors), verticesAndColors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	/// create vertex shader from vertex shader source file
	MyShader shader1;
	shader1.setShaderTypeAsVertex();
	shader1.readShaderFromFile("vertexShader1.glsl");
	shader1.compileShader();

	int success;
	char* debugData = NULL;
	shader1.getShaderCompilationStatus(success, &debugData, 512);
	if (!success)
	{
		ERROR_LOG("ERROR::MYSHADER::COMPILATION_FAILED", debugData);
	}

	/// create a fragment shader from fragment shader source file
	MyShader shader2;
	shader2.setShaderTypeAsFragment();
	shader2.readShaderFromFile("fragmentShader1.glsl");
	shader2.compileShader();
	shader2.getShaderCompilationStatus(success, &debugData, 512);
	if (!success)
	{
		ERROR_LOG("ERROR::MYSHADER::COMPILATION_FAILED", debugData);
	}

	/// create a shader program
	MyShaderProgram shaderProgramObject(&shader1, &shader2);
	shaderProgramObject.linkShaderProgram();
	shaderProgramObject.getShaderLinkingStatus(success, &debugData, 512);
	if (!success)
	{
		ERROR_LOG("ERROR::MYSHADERPROGRAM::LINKING_FAILED", debugData);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		double time = glfwGetTime();
		double greenTint = (sin(time) / 2.0f) + 0.5f;
		int uniformColorPos = glGetUniformLocation(shaderProgramObject.getProgramID(), "timeColor");
		
		/// draw object
		shaderProgramObject.use();
		if (uniformColorPos != -1)
		{
			glUniform3f(uniformColorPos, greenTint, greenTint, greenTint);
		}

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		processEvent(window);
		
		/// stub rendering events		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}