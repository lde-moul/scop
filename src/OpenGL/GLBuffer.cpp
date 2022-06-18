#include "GLBuffer.hpp"
#include "GLError.hpp"

GLuint GLBuffer::getID() const
{
	return id;
}

GLuint GLBuffer::getStride() const
{
	return stride;
}

void GLBuffer::bind()
{
	glBindBuffer(type, id);
	if (glGetError())
		throw GLError("failed to bind buffer");
}

void GLBuffer::set(GLenum type, void const *data, GLsizeiptr size, GLsizei stride)
{
	glDeleteBuffers(1, &id);

	this->type = type;
	this->stride = stride;

	glCreateBuffers(1, &id);
	if (glGetError())
		throw GLError("failed to create buffer");

	glNamedBufferData(id, size, data, GL_STATIC_DRAW);
	if (glGetError())
		throw GLError("failed to set buffer data");
}

GLBuffer::GLBuffer() : id(0) {}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &id);
}
