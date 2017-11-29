#include "namaste/Wrapper.h"

void enableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void disableWireframe()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

GLint getNumExtensions()
{
	GLint num = -1;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num);
	return num;
}

bool extensionSupported(const std::string &aExtName)
{
	GLint num = getNumExtensions();
	for (GLint i = 0; i < num; ++i)
	{
		if (aExtName == (char*)glGetStringi(GL_EXTENSIONS, i))
		{
			return true;
		}
	}
	return false;
}