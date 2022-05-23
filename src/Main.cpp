#include "Model.hpp"
#include "GLBuffer.hpp"
#include "GLError.hpp"
#include "GLProgram.hpp"
#include "GLShader.hpp"
#include "GLVAO.hpp"

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

	glViewport(0, 0, 1024, 1024);

	return window;
}

static void loadShaders(GLProgram & program, GLShader & vertexShader, GLShader & fragmentShader)
{
	std::string vertexShaderCode(R"""(
		#version 450 core

		layout (location = 0) in vec3 aPos;

		void main()
		{
			gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
		}
	)""");
	vertexShader.load(GL_VERTEX_SHADER, vertexShaderCode);
	program.attachShader(vertexShader);

	std::string fragmentShaderCode(R"""(
		#version 330 core

		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		}
	)""");
	fragmentShader.load(GL_FRAGMENT_SHADER, fragmentShaderCode);
	program.attachShader(fragmentShader);

	program.link();
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

		GLProgram program;
		GLShader vertexShader;
		GLShader fragmentShader;
		loadShaders(program, vertexShader, fragmentShader);

		GLVAO vao;
		vao.addAttribute(3, GL_FLOAT, GL_FALSE, 0); // Error here

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f,  0.5f, 0.0f
		};
		GLBuffer vbo(GL_ARRAY_BUFFER, vertices, sizeof(vertices));

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.8f, 0.5f, 0.5f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			vao.bind();
			vao.bindVBO(vbo, 3 * sizeof(GLfloat));
			program.use();
			glDrawArrays(GL_TRIANGLES, 0, 3);

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
	catch (GLError & e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}
