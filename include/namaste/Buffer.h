#pragma once

#include "Platform.h"

class Buffer;
using BufferRef = std::shared_ptr<Buffer>;

class Buffer
{
	
public:

	Buffer(GLenum aTarget, const void *aData = nullptr, GLenum aUsage = GL_STATIC_DRAW);

	template<typename T>
	Buffer(GLenum aTarget, const std::vector<T> &aData, GLenum aUsage = GL_STATIC_DRAW) :
		mTarget(aTarget)
	{
		glGenBuffers(1, &mId);
		bind();
		glBufferData(mTarget, aData.size() * sizeof(T), aData.data(), aUsage);
		unbind();
	}

	template<typename T>
	static inline BufferRef create(GLenum aTarget, const std::vector<T> &aData, GLenum aUsage = GL_STATIC_DRAW)
	{
		return BufferRef(new Buffer(aTarget, aData, aUsage));
	}

	static inline BufferRef create(GLenum aTarget, const void *aData = nullptr, GLenum aUsage = GL_STATIC_DRAW)
	{
		return BufferRef(new Buffer(aTarget, aData, aUsage));
	}

	void bind() const;
	void unbind() const;

private:

	GLuint mId;
	GLenum mTarget;

};