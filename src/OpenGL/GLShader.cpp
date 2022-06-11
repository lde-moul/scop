#include "GLError.hpp"
#include "GLShader.hpp"

GLuint GLShader::getID() const
{
	return id;
}

void GLShader::load(GLenum type, std::string const & code)
{
	glDeleteShader(id);

	id = glCreateShader(type);
	if (id == 0)
	{
		throw GLError("failed to create shader");
	}

	char const * rawCode = code.data();;
	glShaderSource(id, 1, &rawCode, nullptr);

	glCompileShader(id);

	GLint success;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar log[1024];
		glGetShaderInfoLog(id, sizeof(log), nullptr, log);
		throw GLError(log);
	}
}

GLShader::GLShader() : id(0) {}

GLShader::~GLShader()
{
	glDeleteShader(id);
}
