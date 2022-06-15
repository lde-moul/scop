#include "App.hpp"
#include "OpenGL/GLError.hpp"
#include "Util.hpp"

#include <cmath>

#include <iostream> // !!!

void App::handleTick(double timeStep)
{
	handleCameraRotation(timeStep);
}

void App::handleCameraRotation(double timeStep)
{
	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	double cursorMoveX = cursorX - oldCursorX;
	double cursorMoveY = cursorY - oldCursorY;
	oldCursorX = cursorX;
	oldCursorY = cursorY;

	float speed = 2 * Util::PI * getSpeedFactor() * timeStep;

	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		cameraDirection = Quaternion();
		cameraSimpleRotation = Vector();
		cameraZoom = -5;
	}

	Vector keyboardAxis;
	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
		keyboardAxis = keyboardAxis + Vector(0, -1);
	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
		keyboardAxis = keyboardAxis + Vector(0, 1);
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
		keyboardAxis = keyboardAxis + Vector(-1, 0);
	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
		keyboardAxis = keyboardAxis + Vector(1, 0);
	keyboardAxis = keyboardAxis.normalize();

	Vector mouseAxis = Vector(cursorMoveY, cursorMoveX) / 32;

	cameraSimpleRotation = cameraSimpleRotation + keyboardAxis / 2 * speed;
	cameraSimpleRotation = Vector(std::fmod(cameraSimpleRotation.x, 2 * Util::PI), std::fmod(cameraSimpleRotation.y, 2 * Util::PI));

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		cameraSimpleRotation = cameraSimpleRotation + mouseAxis * speed;
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
		cameraDirection = Quaternion::getRotation(mouseAxis, speed * mouseAxis.getLength()) * cameraDirection;

	if (autoRotating)
		cameraDirection = Quaternion::getRotation(Vector(0, 1, 0), 2 * Util::PI / 10 * timeStep) * cameraDirection;
}

void App::handleScrolling(double, double y)
{
	cameraZoom += y / 4 * getSpeedFactor();
	cameraZoom = std::min(std::max(cameraZoom, -100.f), 10.f);
}

static void scrollCallback(GLFWwindow *window, double x, double y)
{
	static_cast<App*>(glfwGetWindowUserPointer(window))->handleScrolling(x, y);
}

void App::handleKey(int key, int, int action, int)
{
	if (action != GLFW_PRESS)
		return;

	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, true);
		break;

	case GLFW_KEY_1:
		viewType = ViewType::Uniform;
		loadShaders();
		break;
	case GLFW_KEY_2:
		viewType = ViewType::Colors;
		loadShaders();
		break;
	case GLFW_KEY_3:
		viewType = ViewType::Texture;
		loadShaders();
		break;
	case GLFW_KEY_4:
		viewType = ViewType::Wireframe;
		loadShaders();
		break;

	case GLFW_KEY_R:
		autoRotating = !autoRotating;
		break;
	}
}

static void keyCallback(GLFWwindow *window, int key, int code, int action, int modifier)
{
	static_cast<App*>(glfwGetWindowUserPointer(window))->handleKey(key, code, action, modifier);
}

float App::getSpeedFactor()
{
	bool shiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));
	return shiftPressed ? 0.25f : 1.f;
}

void App::drawModel(size_t numElements)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	Matrix projection = Matrix::perspective(Util::degreesToRadians(90), aspectRatio, 0.1f, 100.f);

	Matrix viewTranslation = Matrix::translation(0, 0, cameraZoom);
	Matrix viewRotationX = Quaternion::getRotation(Vector(cameraSimpleRotation.x, 0), std::abs(cameraSimpleRotation.x)).getMatrix();
	Matrix viewRotationY = Quaternion::getRotation(Vector(0, cameraSimpleRotation.y), std::abs(cameraSimpleRotation.y)).getMatrix();
	Matrix viewRotation = cameraDirection.getMatrix() * viewRotationY * viewRotationX;
	Matrix view = viewTranslation * viewRotation;

	Matrix model = Matrix::translation(0, 0, 0);

	program.use();
	program.setUniform("matrix", projection * view * model);

	vao.bind();
	vao.bindVBO(vbo);
	vao.bindEBO(ebo);

	if (viewType == ViewType::Wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(1.f);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	texture.bind();

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

void App::loop()
{
	double lastFrame = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		handleTick(now - lastFrame);
		lastFrame = now;

		glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawModel(vertexIndices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void App::initialiseWindow()
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwGetCursorPos(window, &oldCursorX, &oldCursorY);
}

void App::loadAssets(std::string const & modelFileName)
{
	model.load(modelFileName);
	tga.load("resources/norminet.tga");
}

void App::initialiseRendering()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glClearDepthf(0.f);

	loadShaders();

	vao.addAttribute(3, GL_FLOAT, GL_FALSE, 0);
	vao.addAttribute(2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	vertices = model.getVerticesAsArray();
	vbo.set(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(float), 5 * sizeof(float));

	vertexIndices = model.getFacesAsArray();
	ebo.set(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.data(), vertexIndices.size() * sizeof(unsigned int), sizeof(unsigned int));

	texture.set(tga);
}

void App::loadShaders()
{
	program.reset();

	vertexShader.load(GL_VERTEX_SHADER, "resources/Shader.vs");
	program.attachShader(vertexShader);

	std::string fileName;
	switch (viewType)
	{
		case ViewType::Uniform  : fileName = "Uniform.fs"; break;
		case ViewType::Colors   : fileName = "Colors.fs" ; break;
		case ViewType::Texture  : fileName = "Texture.fs"; break;
		case ViewType::Wireframe: fileName = "Colors.fs" ; break;
	}
	fragmentShader.load(GL_FRAGMENT_SHADER, "resources/" + fileName);
	program.attachShader(fragmentShader);

	program.link();
}

void App::run(std::vector<std::string> const & args)
{
	initialiseWindow();
	loadAssets(args[1]);
	initialiseRendering();
	loop();
}

App::App(GLFWwindow *window) : window(window), cameraZoom(-5), viewType(ViewType::Colors), autoRotating(false) {}

App::~App() {}
