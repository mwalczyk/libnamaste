#include "stdafx.h"
#include "ResourceManager.h"

namespace breakout {

	// Instantiate static variables
	std::map<std::string, Texture> ResourceManager::textures;
	std::map<std::string, GlslProgram> ResourceManager::shaders;

	GlslProgram ResourceManager::loadShader(const std::string &name, const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile)
	{
		shaders[name] = loadShaderFromFile(vertFile, fragFile, geomFile);
		return shaders[name];
	}

	GlslProgram& ResourceManager::getShader(const std::string &name) 
	{
		auto it = shaders.find(name);
		if (it != shaders.end())
		{
			return (*it).second;
		}
	}

	Texture ResourceManager::loadTexture(const std::string &name, const GLchar *file, GLboolean alpha)
	{
		textures[name] = loadTextureFromFile(file, alpha);
		return textures[name];
	}

	Texture& ResourceManager::getTexture(const std::string &name) 
	{
		auto it = textures.find(name);
		if (it != textures.end())
		{
			return (*it).second;
		}
	}

	void ResourceManager::clear()
	{
		for (auto &item : shaders)
		{
			glDeleteProgram(item.second.programId);
		}
		shaders.clear();

		for (auto &item : textures)
		{
			glDeleteTextures(1, &item.second.texId);
		}
		textures.clear();
	}

	GlslProgram ResourceManager::loadShaderFromFile(const GLchar *vertFile, const GLchar *fragFile, const GLchar *geomFile)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;

		try
		{
			// Open files
			std::ifstream vertexShaderFile(vertFile);
			std::ifstream fragmentShaderFile(fragFile);
			if (!vertexShaderFile.is_open()) {
				std::cout << " Failed to open" << std::endl;
			}
			std::stringstream vertSS, fragSS;

			// Read file's buffer contents into streams
			vertSS << vertexShaderFile.rdbuf();
			fragSS << fragmentShaderFile.rdbuf();

			// close file handlers
			vertexShaderFile.close();
			fragmentShaderFile.close();

			// Convert stream into string
			vertexCode = vertSS.str();
			fragmentCode = fragSS.str();

			// If geometry shader path is present, also load a geometry shader
			if (geomFile != nullptr)
			{
				std::ifstream geometryShaderFile(geomFile);
				std::stringstream geomSS;
				geomSS << geometryShaderFile.rdbuf();
				geometryShaderFile.close();
				geometryCode = geomSS.str();
			}
		}
		catch (std::exception e)
		{
			std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
		}

		const GLchar *vertSrc = vertexCode.c_str();
		const GLchar *fragSrc = fragmentCode.c_str();
		const GLchar *geomSrc = geometryCode.c_str();
		
		GlslProgram shader;
		shader.compile(vertSrc, fragSrc, geomFile != nullptr ? geomSrc : nullptr);

		return shader;
	}

	Texture ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
	{
		Texture texture;

		if (alpha)
		{
			// By default, Texture objects are GL_RGB
			texture.internalFormat = GL_RGBA;
			texture.imageFormat = GL_RGBA;
		}

		int width, height;
		unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.imageFormat == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
		texture.generate(width, height, image);
		SOIL_free_image_data(image);

		return texture;
	}

} //namespace breakout
