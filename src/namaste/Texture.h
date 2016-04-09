#pragma once

#include <GL\glew.h>
#include <memory>

namespace breakout {

	class Texture;
	using TextureRef = std::shared_ptr<Texture>;

	class Texture
	{
	public:
		Texture();
		~Texture();

		static inline TextureRef create()
		{
			return TextureRef(new Texture);
		}

		void generate(GLuint aWidth, GLuint aHeight, unsigned char *data);
		void bind() const;
		void unbind() const;

		GLuint texId;
		GLuint width;
		GLuint height;
		GLuint internalFormat;
		GLuint imageFormat;
		GLuint wrapS;
		GLuint wrapT;
		GLuint filterMin;
		GLuint filterMax;
	private:
	};

} // namespace breakout