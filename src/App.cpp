#include "App.hpp"
#include "OpenGL/GLError.hpp"
#include "Util.hpp"

#include <iostream> // !!!

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

void App::handleInputs(double timeStep)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	ViewType newViewType = viewType;
	if (glfwGetKey(window, GLFW_KEY_1))
	{
		newViewType = ViewType::Uniform;
	}
	if (glfwGetKey(window, GLFW_KEY_2))
	{
		newViewType = ViewType::Colors;
	}
	if (glfwGetKey(window, GLFW_KEY_3))
	{
		newViewType = ViewType::Texture;
	}
	if (glfwGetKey(window, GLFW_KEY_4))
	{
		newViewType = ViewType::Wireframe;
	}
	if (newViewType != viewType)
	{
		viewType = newViewType;
		loadShaders();
	}

	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	double cursorMoveX = cursorX - oldCursorX;
	double cursorMoveY = cursorY - oldCursorY;
	oldCursorX = cursorX;
	oldCursorY = cursorY;

	handleCameraRotation(timeStep, cursorMoveX, cursorMoveY);
}

void App::handleCameraRotation(double timeStep, double cursorMoveX, double cursorMoveY)
{
	Vector keyboardRotation;
	if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_LEFT))
	{
		keyboardRotation = keyboardRotation + Vector(0, 1, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_D) || glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		keyboardRotation = keyboardRotation + Vector(0, -1, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_W) || glfwGetKey(window, GLFW_KEY_UP))
	{
		keyboardRotation = keyboardRotation + Vector(1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_S) || glfwGetKey(window, GLFW_KEY_DOWN))
	{
		keyboardRotation = keyboardRotation + Vector(-1, 0, 0);
	}
	Vector mouseRotation = Vector(-cursorMoveY, -cursorMoveX, 0) / 32;

	Vector mouseRotation = Vector(-cursorMoveY, cursorMoveX, 0) / 32;

	cameraRotation = cameraRotation + (keyboardRotation + mouseRotation) * 2 * Util::PI * getSpeedFactor() * timeStep;
}

void App::handleScrolling(double, double y)
{
	cameraZoom += y * getSpeedFactor();
}

float App::getSpeedFactor()
{
	bool shiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));
	return shiftPressed ? 0.25f : 1.f;
}

static void scrollCallback(GLFWwindow *window, double x, double y)
{
	static_cast<App*>(glfwGetWindowUserPointer(window))->handleScrolling(x, y);
}

void App::drawModel(size_t numElements)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	Matrix projection = Matrix::perspective(Util::degreesToRadians(90), aspectRatio, 0.1f, 100.f);

	Matrix viewTranslation = Matrix::translation(0, 0, cameraZoom);
	Matrix viewRotationX = Matrix::rotationX(cameraRotation.getX());
	Matrix viewRotationY = Matrix::rotationY(cameraRotation.getY());
	Matrix view = viewTranslation * viewRotationX * viewRotationY;

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

void App::run(std::vector<std::string> const & args)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwGetCursorPos(window, &oldCursorX, &oldCursorY);

	model.load(args[1]);
	tga.load("resources/norminet.tga");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_GREATER);
	glClearDepthf(0.f);

	loadShaders();

	vao.addAttribute(3, GL_FLOAT, GL_FALSE, 0);
	vao.addAttribute(2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	std::vector<float> vertices = model.getVerticesAsArray();
	vbo.set(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(float), 5 * sizeof(float));

	std::vector<unsigned int> vertexIndices = model.getFacesAsArray();
	ebo.set(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.data(), vertexIndices.size() * sizeof(unsigned int), sizeof(unsigned int));

	texture.set(tga);

	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		handleInputs(now - lastFrame);
		lastFrame = now;

		glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		drawModel(vertexIndices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

App::App(GLFWwindow *window) : window(window), cameraRotation(0, 0, 0), cameraZoom(-5), viewType(ViewType::Colors) {}

App::~App() {}
