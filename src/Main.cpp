#include "Model.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>
#include <iostream>

static GLFWwindow *createWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1024, 1024, "scop", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "Error: " << glewGetErrorString(error) << std::endl;
		return nullptr;
	}

	glViewport(0, 0, 512, 512);

	return window;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "wrong number of arguments" << std::endl;
		return 1;
	}

	try
	{
		Model model(argv[1]);

		GLFWwindow *window = createWindow();

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.8f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		glfwTerminate();
	}
	catch (Model::LoadError & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
