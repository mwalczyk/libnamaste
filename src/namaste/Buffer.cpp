#include "namaste/Buffer.h"

Buffer::Buffer(GLenum aTarget, const void *aData, GLenum aUsage) :
	mTarget(aTarget)
{
	glGenBuffers(1, &mId);
	bind();
	glBufferData(mTarget, sizeof(aData), aData, aUsage);
	unbind();
}

void Buffer::bind() const
{
	glBindBuffer(mTarget, mId);
}

void Buffer::unbind() const
{
	glBindBuffer(mTarget, 0);
}
