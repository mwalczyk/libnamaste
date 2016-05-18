#pragma once

#include "Platform.h"
#include "Gl.h"

class Vao
{

public:

	Vao();
	~Vao();

	void bind() const;
	void unbind() const;
	void vertexAttrPointer();
	
	struct VertexAttrFormat
	{
		VertexAttrFormat() :
			mIndex(0), mSize(0), mType(GL_FLOAT), mNormalized(GL_FALSE), mStride(0), mOffset(0)
		{}

		VertexAttrFormat(GLuint aIndex, GLint aSize, GLenum aType, GLboolean aNormalized, GLsizei aStride, const GLvoid *aOffset) :
			mIndex(aIndex), mSize(aSize), mType(aType), mNormalized(aNormalized), mStride(aStride), mOffset(aOffset)
		{}
		
		GLuint mIndex;			// ex. 0
		GLint mSize;			// ex. 3
		GLenum mType;			// ex. GLfloat
		GLboolean mNormalized;	// ex. GL_FALSE
		GLsizei	mStride;		// ex. 0
		const GLvoid *mOffset;	// ex. 0
	};

private:

	GLuint mId;
	std::map<GLuint, BufferRef> mVertexAttrBindings;

};
