#ifndef SCOP_APP_HPP
#define SCOP_APP_HPP

#include "Model/Model.hpp"
#include "OpenGL/GLBuffer.hpp"
#include "OpenGL/GLProgram.hpp"
#include "OpenGL/GLShader.hpp"
#include "OpenGL/GLVAO.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class App
{
private:
	GLFWwindow *window;
	Model model;
	GLProgram program;
	GLShader vertexShader;
	GLShader fragmentShader;
	GLVAO vao;
	GLBuffer vbo;
	GLBuffer ebo;
	float cameraAngle;
	double oldCursorX;
	double oldCursorY;

	void loadShaders();
	void handleInputs(double timeStep);
	void drawModel(size_t numElements);

public:
	void run(std::vector<std::string> const & args);

	App(GLFWwindow *window);
	~App();

};

#endif
