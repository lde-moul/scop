#include "GLError.hpp"
#include "GLVAO.hpp"

void GLVAO::bind()
{
	glBindVertexArray(id);
	if (glGetError())
		throw GLError("failed to bind vertex array");
}

void GLVAO::bindVBO(GLBuffer & vbo)
{
	glVertexArrayVertexBuffer(id, 0, vbo.getID(), 0, vbo.getStride());
	if (glGetError())
		throw GLError("failed to bind vertex buffer to vertex array");
}

void GLVAO::bindEBO(GLBuffer & ebo)
{
	glVertexArrayElementBuffer(id, ebo.getID());
	if (glGetError())
		throw GLError("failed to bind element buffer to vertex array");
}

void GLVAO::addAttribute(GLint size, GLenum type, GLboolean normalized, GLuint offset)
{
	glEnableVertexArrayAttrib(id, numAttributes);
	glVertexArrayAttribFormat(id, numAttributes, size, type, normalized, offset);
	glVertexArrayAttribBinding(id, numAttributes, 0);
	if (glGetError())
		throw GLError("failed to add attribute to vertex array");
	numAttributes++;
}

GLVAO::GLVAO() : numAttributes(0)
{
	glCreateVertexArrays(1, &id);
	if (glGetError())
		throw GLError("failed to create vertex array");
}

GLVAO::~GLVAO()
{
	glDeleteVertexArrays(1, &id);
}
