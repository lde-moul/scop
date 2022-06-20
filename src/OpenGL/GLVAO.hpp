#ifndef SCOP_GLVAO_HPP
#define SCOP_GLVAO_HPP

#include "GLBuffer.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>

class GLVAO
{
private:
	GLuint id;
	size_t numAttributes;

public:
	void bind();
	void bindVBO(GLBuffer & vbo);
	void bindEBO(GLBuffer & ebo);
	void addAttribute(GLint size, GLenum type, GLboolean normalized, GLuint offset);

	GLVAO();
	GLVAO(GLVAO const & other) = delete;
	GLVAO & operator=(GLVAO const & other) = delete;
	~GLVAO();

};

#endif
