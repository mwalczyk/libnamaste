#pragma once

#include "Platform.h"
#include "Gl.h"
#include "Window.h"

class Context;
using ContextRef = std::shared_ptr<Context>;

class Context
{

public:
	
	Context(const WindowRef &aWindowRef);
	~Context();

	static inline ContextRef create(const WindowRef &aWindowRef)
	{
		return ContextRef(new Context(aWindowRef));
	}

	const std::vector<GlslProgramRef>& getGlslProgramStack() const { return mGlslProgramStack; };
	HDC getDeviceContext() const { return mDc; };

private:

	bool createGlContext();
	void releaseGlContext();
	void resizeGlContext(GLint width, GLint height);

	std::vector<GlslProgramRef> mGlslProgramStack;
	WindowRef mWindowRef;

	HDC mDc;
	HGLRC mGlrc;
	RECT mScreenRect;
	RECT mClientRect;
};