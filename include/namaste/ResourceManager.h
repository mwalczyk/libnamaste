#pragma once

#include "../Namaste/Platform.h"
#include "GlslProgram.h"
#include "Texture.h"
#include <map>
#include <sstream>
#include <fstream>

class ResourceManager
{
public:
	ResourceManager() = delete;

	static GlslProgram loadShader(const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile = nullptr);
	static Texture loadTexture(const GLchar *file, GLboolean alpha = GL_FALSE);

private:
	static GlslProgram loadShaderFromFile(const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile = nullptr);
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
};
