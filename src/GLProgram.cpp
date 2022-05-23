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

void GLProgram::use()
{
	glUseProgram(id);
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
