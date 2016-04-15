#include "../include/namaste/Texture.h"

Texture::Texture() :
	width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB),
	wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
	glGenTextures(1, &texId);
}

Texture::~Texture()
{
}

void Texture::generate(GLuint aWidth, GLuint aHeight, unsigned char *data)
{
	width = aWidth;
	height = aHeight;

	// Create the texture
	bind();
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);

	// Set the texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

	// Unbind the texture
	unbind();
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texId);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
