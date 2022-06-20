#ifndef SCOP_GLSHADER_HPP
#define SCOP_GLSHADER_HPP

#include "glew.h"
#include <GLFW/glfw3.h>
#include <string>

class GLShader
{
private:
	GLuint id;

public:
	GLuint getID() const;
	void load(GLenum type, std::string const & fileName);

	GLShader();
	GLShader(GLShader const & other) = delete;
	GLShader & operator=(GLShader const & other) = delete;
	~GLShader();

};

#endif
