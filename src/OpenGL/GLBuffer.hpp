#ifndef SCOP_GLBUFFER_HPP
#define SCOP_GLBUFFER_HPP

#include <vector>

#include "glew.h"
#include <GLFW/glfw3.h>

class GLBuffer
{
private:
	GLenum type;
	GLuint id;
	GLsizei stride;

public:
	GLuint getID() const;
	GLuint getStride() const;
	void bind();
	void set(GLenum type, void const *data, GLsizeiptr size, GLsizei stride);

	GLBuffer();
	GLBuffer(GLBuffer const & other) = delete;
	GLBuffer & operator=(GLBuffer const & other) = delete;
	~GLBuffer();

};

#endif
