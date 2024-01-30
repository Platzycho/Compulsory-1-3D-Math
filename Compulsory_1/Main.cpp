#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Task_1.h"
#include "Task_2.h"	
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float fov = 45.0f;

float cameraSpeed = 0.05f;
float cameraYaw = 0.0f;

int main(){

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

	double number;
	double numOne;
	double numTwo;
	double numThree;
	double numFour;
	double numX;
	double numInterval;

	Task_1 taskOne;
	Task_2 taskTwo;

	std::cout << "For task one: Enter the four numbers in task one in order of the function one by one: ";
	std::cin >> numOne;
	std::cin >> numTwo;
	std::cin >> numThree;
	std::cin >> numFour;
	std::cout << "Now enter the x value for task 1: ";
	std::cin >> numX;

	auto start_Function_One = std::chrono::high_resolution_clock::now();

	taskOne.taskOneFunction(numOne, numTwo, numThree, numFour, numX);

	auto stop_Function_One = std::chrono::high_resolution_clock::now();

	std::cout << "Enter the value of X for task 2 here: ";
	std::cin >> number;

	if(!std::cin) {
		std::cout << "Invalid input!" << std::endl;
		return 1;
	}

	auto start_Function_Two = std::chrono::high_resolution_clock::now();

	taskTwo.taskTwoFunction(number);

	auto stop_Function_Two = std::chrono::high_resolution_clock::now();

	auto duration_Merge_One = std::chrono::duration_cast<std::chrono::milliseconds>(stop_Function_One - start_Function_One);
	std::cout << "\n Time taken for function one: " << duration_Merge_One.count() << " milliseconds" << std::endl;

	auto duration_Merge_Two = std::chrono::duration_cast<std::chrono::milliseconds>(stop_Function_Two - start_Function_Two);
	std::cout << "\n Time taken for function one: " << duration_Merge_Two.count() << " milliseconds" << std::endl;

	std::cout << "Enter the amount of intervals: ";
	std::cin >> numInterval;

	taskTwo.taskTwoInterval(numInterval);

	taskTwo.taskTwoColors(numInterval);

	std::vector<float> vertices = taskTwo.taskTwoInterval(numInterval);
	std::vector<float> colors = taskTwo.taskTwoColors(numInterval);

	size_t numberOfPoints = vertices.size() /2;

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO_vertices;
	glGenBuffers(1, &VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	GLuint VBO_colors;
	glGenBuffers(1, &VBO_colors);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_colors);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), colors.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindVertexArray(1);
	
	
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
		glDrawArrays(GL_LINE_STRIP, 0, numberOfPoints);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();	
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO_vertices);
	glDeleteBuffers(1, &VBO_colors);
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