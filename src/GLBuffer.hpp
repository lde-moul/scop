#ifndef SCOP_GLBUFFER_HPP
#define SCOP_GLBUFFER_HPP

#include "glew.h"
#include <GLFW/glfw3.h>

class GLBuffer
{
private:
	GLenum type;
	GLuint id;

public:
	GLuint getID() const;
	void bind();

	GLBuffer(GLenum type, GLvoid *data, GLsizeiptr size);
	~GLBuffer();

};

#endif
