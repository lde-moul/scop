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

	GLProgram backgroundProgram;
	GLShader backgroundVertexShader;
	GLShader backgroundFragmentShader;

	GLVAO vao;
	GLBuffer vbo;
	GLBuffer ebo;
	GLTexture texture;
	std::vector<float> vertices;
	std::vector<unsigned int> vertexIndices;

	GLVAO backgroundVAO;
	GLBuffer backgroundVBO;
	GLBuffer backgroundEBO;

	void handleTick(double timeStep);
	void handleCameraRotation(double timeStep);
	float getSpeedFactor();
	void drawBackground();
	Matrix createModelMatrix();
	void drawModel();
	void loop();
	void initialiseWindow();
	void loadAssets(std::string const & modelFileName);
	void initialiseBackgroundRendering();
	void initialiseModelRendering();
	void initialiseRendering();
	void loadShaders();

public:
	void run(std::vector<std::string> const & args);
	void handleKey(int key, int code, int action, int modifier);
	void handleScrolling(double x, double y);

	App(GLFWwindow *window);
	~App();

};

#endif
