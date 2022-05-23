#include "GLError.hpp"
#include "GLVAO.hpp"

void GLVAO::bind()
{
	glBindVertexArray(id);
}

void GLVAO::bindVBO(GLBuffer & vbo, GLsizei stride)
{
	glVertexArrayVertexBuffer(id, 0, vbo.getID(), 0, stride);
}

void GLVAO::addAttribute(GLint size, GLenum type, GLboolean normalized, GLuint offset)
{
	glEnableVertexArrayAttrib(id, numAttributes);
	glVertexArrayAttribFormat(id, numAttributes, size, type, normalized, offset);
	glVertexArrayAttribBinding(id, numAttributes, 0);
	numAttributes++;
}

GLVAO::GLVAO() : numAttributes(0)
{
	glCreateVertexArrays(1, &id);
}

GLVAO::~GLVAO()
{
	glDeleteVertexArrays(1, &id);
}
