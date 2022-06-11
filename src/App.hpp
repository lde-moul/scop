#ifndef SCOP_APP_HPP
#define SCOP_APP_HPP

#include "Model/Model.hpp"
#include "OpenGL/GLBuffer.hpp"
#include "OpenGL/GLProgram.hpp"
#include "OpenGL/GLShader.hpp"
#include "OpenGL/GLTexture.hpp"
#include "OpenGL/GLVAO.hpp"
#include "TGA.hpp"
#include "Vector.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class App
{
private:
	enum class ViewType
	{
		Uniform,
		Colors,
		Texture,
		Wireframe
	};

	GLFWwindow *window;
	Model model;
	TGA tga;

	Vector cameraRotation;
	float cameraZoom;
	ViewType viewType;

	double oldCursorX;
	double oldCursorY;

	GLProgram program;
	GLShader vertexShader;
	GLShader fragmentShader;

	GLVAO vao;
	GLBuffer vbo;
	GLBuffer ebo;
	GLTexture texture;

	void loadShaders();
	void handleInputs(double timeStep);
	void handleCameraRotation(double timeStep, double cursorMoveX, double cursorMoveY);
	float getSpeedFactor();
	void drawModel(size_t numElements);

public:
	void run(std::vector<std::string> const & args);
	void handleScrolling(double x, double y);

	App(GLFWwindow *window);
	~App();

};

#endif
