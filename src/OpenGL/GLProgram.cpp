#include "GLError.hpp"
#include "GLProgram.hpp"

void GLProgram::attachShader(GLShader const & shader)
{
	glAttachShader(id, shader.getID());
	if (glGetError())
		throw GLError("failed to attach shader");
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
		throw GLError("failed to create program");
}

void GLProgram::use()
{
	glUseProgram(id);
	if (glGetError())
		throw GLError("failed to use program");
}

GLint GLProgram::getUniformLocation(std::string const & name)
{
	GLint location = glGetUniformLocation(id, name.c_str());
	if (location == -1)
		throw GLError("failed to get uniform location");
	return location;
}

void GLProgram::setUniform(std::string const & name, float const * array, size_t size)
{
	glProgramUniform1fv(id, getUniformLocation(name), size, array);
}

void GLProgram::setUniform(std::string const & name, Matrix const & matrix)
{
	glProgramUniformMatrix4fv(id, getUniformLocation(name), 1, GL_TRUE, matrix.getArray());
}

GLProgram::GLProgram()
{
	id = glCreateProgram();
	if (id == 0)
		throw GLError("failed to create program");
}

GLProgram::~GLProgram()
{
	glDeleteProgram(id);
}
