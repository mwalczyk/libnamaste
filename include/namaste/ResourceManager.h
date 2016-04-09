#pragma once

#include <GL\glew.h>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <SOIL.h>
#include "GlslProgram.h"
#include "Texture.h"

namespace breakout {

	class ResourceManager
	{
	public:
		ResourceManager() = delete;
		
		static GlslProgram loadShader(const std::string &name, const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile = nullptr);
		static GlslProgram& getShader(const std::string &name);
		static Texture loadTexture(const std::string &name, const GLchar *file, GLboolean alpha = GL_FALSE);
		static Texture& getTexture(const std::string &name);
		static void clear();

		static std::map<std::string, GlslProgram> shaders;
		static std::map<std::string, Texture> textures;
	private:
		static GlslProgram loadShaderFromFile(const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile = nullptr);
		static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
	};

} //namespace breakout