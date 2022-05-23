#include "GLBuffer.hpp"
#include "GLError.hpp"

GLuint GLBuffer::getID() const
{
	return id;
}

void GLBuffer::bind()
{
	glBindBuffer(type, id);
}

GLBuffer::GLBuffer(GLenum type, GLvoid *data, GLsizeiptr size) : type(type)
{
	glCreateBuffers(1, &id);

	glNamedBufferData(id, size, data, GL_STATIC_DRAW);
	if (glGetError())
	{
		throw GLError("failed to set buffer data");
	}
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &id);
}
