#include "GLError.hpp"
#include "GLProgram.hpp"

void GLProgram::attachShader(GLShader const & shader)
{
	glAttachShader(id, shader.getID());
}

void GLProgram::link()
{
	glLinkProgram(id);

	GLint success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success)
	{
		GLchar log[1024];
		glGetProgramInfoLog(id, sizeof(log), nullptr, log);
		throw GLError(log);
	}
}

void GLProgram::reset()
{
	glDeleteProgram(id);

	id = glCreateProgram();
	if (id == 0)
	{
		throw GLError("failed to create program");
	}
}

void GLProgram::use()
{
	glUseProgram(id);
}

void GLProgram::setUniform(std::string const & name, Matrix const & matrix)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	glProgramUniformMatrix4fv(id, location, 1, GL_TRUE, matrix.getArray());
}

GLProgram::GLProgram()
{
	id = glCreateProgram();
	if (id == 0)
	{
		throw GLError("failed to create program");
	}
}

GLProgram::~GLProgram()
{
	glDeleteProgram(id);
}
