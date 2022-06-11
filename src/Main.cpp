#include "App.hpp"
#include "OpenGL/GLError.hpp"

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
		throw GLError("failed to create window");
	}

	glfwMakeContextCurrent(window);

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		throw GLError(reinterpret_cast<char const *>(glewGetErrorString(error)));
	}

	glViewport(0, 0, 1024, 1024);

	return window;
}

int main(int argc, char **argv)
{
	std::vector<std::string> args;
	for (int i = 0; i < argc; i++)
	{
		args.push_back(argv[i]);
	}

	if (args.size() != 2)
	{
		std::cerr << "wrong number of arguments" << std::endl;
		return 1;
	}

	try
	{
		App app(createWindow());
		app.run(args);
		glfwTerminate();
	}
	catch (Model::LoadError & e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		return 1;
	}
	catch (TGA::LoadError & e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		return 1;
	}
	catch (GLError & e)
	{
		std::cerr << e.what() << std::endl;
		glfwTerminate();
		return 1;
	}

	return 0;
}
