#include "App.hpp"
#include "OpenGL/GLError.hpp"
#include "Util.hpp"

#include <iostream> // !!!

void App::loadShaders()
{
	std::string vertexShaderCode(R"""(
		#version 450 core

		layout (location = 0) in vec3 position;

		uniform mat4 matrix;

		void main()
		{
			gl_Position = matrix * vec4(position, 1.f);
		}
	)""");
	vertexShader.load(GL_VERTEX_SHADER, vertexShaderCode);
	program.attachShader(vertexShader);

	std::string fragmentShaderCode(R"""(
		#version 450 core

		out vec4 FragColor;

		void main()
		{
			FragColor = vec4(0.4f, 0.4f, 0.8f, 1.0f);
		}
	)""");
	fragmentShader.load(GL_FRAGMENT_SHADER, fragmentShaderCode);
	program.attachShader(fragmentShader);

	program.link();
}

void App::handleInputs(double timeStep)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}

	bool shiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT));
	float cameraSpeedFactor = (shiftPressed ? 0.25f : 1.f);

	float rotateSpeed = 2 * Util::PI * cameraSpeedFactor * timeStep;
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		cameraAngle -= rotateSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		cameraAngle += rotateSpeed;
	}

	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);
	double cursorMoveX = cursorX - oldCursorX;
	double cursorMoveY = cursorY - oldCursorY;
	oldCursorX = cursorX;
	oldCursorY = cursorY;

	cameraAngle += 2 * Util::PI * cursorMoveX / 32 * cameraSpeedFactor * timeStep;
}

void App::drawModel(size_t numElements)
{
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

	Matrix projection = Matrix::perspective(Util::degreesToRadians(90), aspectRatio, 0.1f, 100.f);

	Matrix view = Matrix::translation(0, 0, -5) * Matrix::rotationY(cameraAngle);

	Matrix model = Matrix::translation(0, 0, 0);

	program.use();
	program.setUniform("matrix", projection * view * model);

	vao.bind();
	vao.bindVBO(vbo);
	vao.bindEBO(ebo);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLineWidth(1.f);

	glDrawElements(GL_TRIANGLES, numElements, GL_UNSIGNED_INT, 0);
}

void App::run(std::vector<std::string> const & args)
{
	model.load(args[1]);

	loadShaders();

	vao.addAttribute(3, GL_FLOAT, GL_FALSE, 0);

	std::vector<float> vertices = model.getVerticesAsArray();
	vbo.set(GL_ARRAY_BUFFER, vertices.data(), vertices.size() * sizeof(float), 3 * sizeof(float));

	std::vector<unsigned int> vertexIndices = model.getFacesAsArray();
	ebo.set(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.data(), vertexIndices.size() * sizeof(unsigned int), sizeof(unsigned int));

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwGetCursorPos(window, &oldCursorX, &oldCursorY);

	double lastFrame = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		double now = glfwGetTime();
		handleInputs(now - lastFrame);
		lastFrame = now;

		glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		drawModel(vertexIndices.size());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

App::App(GLFWwindow *window) : window(window), cameraAngle(0) {}

App::~App() {}
