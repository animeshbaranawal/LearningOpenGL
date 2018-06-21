#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include <iostream>

#include "Shader\MyShader.h"
#include "Shader\MyShaderProgram.h"
#include "Texture\MyTexture2D.h"
#include "Camera\MyCamera.h"

#include "Utils\callback_functions.h"
#include "Utils\utils.h"
#include "Utils\stb_image.h"
#include "Utils\globals.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"

float delta_time = 0.0f;
float last_frame;

void processUpDown(GLFWwindow* window, float& ratio, float& angle_z, float& angle_x)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		angle_x += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		angle_x -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		angle_z += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		angle_z -= 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
	{
		if (ratio < 1.0f) ratio += 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
	{
		if (ratio > 0.0f) ratio -= 0.001f;
	}
}

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
	
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	/*unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};*/

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	/// create a data buffer and copy data
	unsigned int VBO_points;
	glGenBuffers(1, &VBO_points);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	/// creata vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_points);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0));
	/// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	/// glEnableVertexAttribArray(1);
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

	/// texture FUN
	MyTexture2D textureObject1, textureObject2;
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	textureObject1.setTextureSize(width, height);
	textureObject1.setTexture(data, GL_RGB, GL_UNSIGNED_BYTE);
	textureObject1.setProperties();
	stbi_image_free(data);
	
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	textureObject2.setTextureSize(width, height);
	textureObject2.setTexture(data, GL_RGBA, GL_UNSIGNED_BYTE);
	textureObject2.setProperties();
	stbi_image_free(data);

	/// Coordinate System FUN
	MyCamera* camera = MyCamera::getInstance();
	camera->setCameraWindow(window);
	camera->switchMode(MyCamera::FORWARD_LOOKING);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 400.0f / 400.0f, 0.1f, 100.0f);

	float ratio = 0.0f;
	float angle_z = 0.0f;
	float angle_x = 0.0f;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	last_frame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		glm::mat4 model;
		model = glm::rotate(model, angle_z, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 rotateTransform;
		rotateTransform = glm::rotate(rotateTransform, angle_x, glm::vec3(1.0f, 0.0f, 0.0f));
		model = model * rotateTransform;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		textureObject1.activateTexture();
		textureObject2.activateTexture(1);
		shaderProgramObject.use();

		glUniform1i(glGetUniformLocation(shaderProgramObject.getProgramID(), "ourTexture1"), 0);
		glUniform1i(glGetUniformLocation(shaderProgramObject.getProgramID(), "ourTexture2"), 1);
		glUniform1f(glGetUniformLocation(shaderProgramObject.getProgramID(), "ratio"), ratio);

		glUniformMatrix4fv(glGetUniformLocation(shaderProgramObject.getProgramID(), "model"), 
			1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramObject.getProgramID(), "projection"),
			1, GL_FALSE, glm::value_ptr(projection));
		
		/// view matrix fun
		float currentFrame = glfwGetTime();
		delta_time = currentFrame - last_frame;
		last_frame = currentFrame;
		glm::mat4 view = camera->getViewMatrix();
		
		glUniformMatrix4fv(glGetUniformLocation(shaderProgramObject.getProgramID(), "view"),
			1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		processEvent(window);
		processUpDown(window, ratio, angle_z, angle_x);

		/// stub rendering events		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}