#ifndef SCOP_GLPROGRAM_HPP
#define SCOP_GLPROGRAM_HPP

#include "GLShader.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>

class GLProgram
{
private:
	GLuint id;

public:
	void attachShader(GLShader const & shader);
	void link();
	void use();

	GLProgram();
	~GLProgram();

};

#endif
