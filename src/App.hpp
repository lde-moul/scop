#ifndef SCOP_APP_HPP
#define SCOP_APP_HPP

#include "Math/Quaternion.hpp"
#include "Math/Vector.hpp"
#include "Model/Model.hpp"
#include "OpenGL/GLBuffer.hpp"
#include "OpenGL/GLProgram.hpp"
#include "OpenGL/GLShader.hpp"
#include "OpenGL/GLTexture.hpp"
#include "OpenGL/GLVAO.hpp"
#include "TGA.hpp"

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

	Quaternion cameraDirection;
	Vector cameraSimpleRotation;
	float cameraZoom;
	ViewType viewType;
	bool autoRotating;

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
	void handleTick(double timeStep);
	void handleInputs(double timeStep);
	void handleCameraRotation(double timeStep, double cursorMoveX, double cursorMoveY);
	float getSpeedFactor();
	void drawModel(size_t numElements);

public:
	void run(std::vector<std::string> const & args);
	void handleKey(int key, int code, int action, int modifier);
	void handleScrolling(double x, double y);

	App(GLFWwindow *window);
	~App();

};

#endif
