#include "GLError.hpp"
#include "GLTexture.hpp"

GLuint GLTexture::getID() const
{
	return id;
}

void GLTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void GLTexture::set(TGA const & tga)
{
	glDeleteTextures(1, &id);

	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	bind();

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tga.getWidth(), tga.getHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, tga.getPixels());
	if (glGetError())
	{
		throw GLError("failed to set texture data");
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLTexture::GLTexture() : id(0) {}

GLTexture::~GLTexture()
{
	glDeleteTextures(1, &id);
}
