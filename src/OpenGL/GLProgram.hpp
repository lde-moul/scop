#ifndef SCOP_GLPROGRAM_HPP
#define SCOP_GLPROGRAM_HPP

#include "GLShader.hpp"
#include "../Math/Matrix.hpp"

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
	void reset();
	void setUniform(std::string const & name, Matrix const & matrix);

	GLProgram();
	~GLProgram();

};

#endif
