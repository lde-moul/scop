#ifndef SCOP_GLTEXTURE_HPP
#define SCOP_GLTEXTURE_HPP

#include "../TGA.hpp"

#include "glew.h"
#include <GLFW/glfw3.h>

class GLTexture
{
private:
	GLuint id;

public:
	GLuint getID() const;
	void bind();
	void set(TGA const & tga);

	GLTexture();
	~GLTexture();

};

#endif
