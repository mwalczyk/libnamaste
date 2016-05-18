#include "namaste/Vao.h"

Vao::Vao()
{
	glGenVertexArrays(1, &mId);
}

void Vao::bind() const
{
	glBindVertexArray(mId);
}

void Vao::unbind() const
{
	glBindVertexArray(0);
}

void Vao::vertexAttrPointer()
{
	
}