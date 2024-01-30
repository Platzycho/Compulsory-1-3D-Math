#ifndef M_PI
#define M_PI 3.14159265358979323846

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <iostream>
#include <algorithm>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float fov = 45.0f;

float cameraSpeed = 0.05f;
float cameraYaw = 0.0f;

int main() {
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD" << std::endl;
		return -1;
	}

	
	Shader ourShader("Shader.vs","Shader.fs");
	
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(fov), (float)800 / (float)600, 0.1f, 100.0f);

	

	const int numVertices = 1000;
	float vertices[numVertices *4];
	

	const float turns = 10.0f;
	const float step = turns * 2 * M_PI/ numVertices;
	const float height = 7.0f;
	const float heightStep = height / numVertices;
	for (int i = 0; i < numVertices; ++i) {
		float angle = i* step;
		float r = angle / (2 * M_PI);
		float z = i * heightStep;
		vertices[i * 3] = r * cos(angle);
		vertices[i * 3 + 1] = r * sin(angle);
		vertices[i * 3 + 2] = z;
	}

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
	
	glEnable(GL_DEPTH_TEST);

	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		//rendering commands
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.use();
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, numVertices);

		glfwSwapBuffers(window);
		glfwPollEvents();
		
	}
		
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return 0;
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	glm::vec3 right = glm::normalize(glm::cross(cameraFront, cameraUp));
	float cameraRotSpeed = 0.5f; 

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    cameraPos -= right * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    cameraPos += right * cameraSpeed; 	
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraYaw -= cameraRotSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraYaw += cameraRotSpeed;

	cameraFront.x = cos(glm::radians(cameraYaw));
    cameraFront.y = 0; 
    cameraFront.z = sin(glm::radians(cameraYaw));
    cameraFront = glm::normalize(cameraFront);
	
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

#endif