#include "namaste/Context.h"

Context::Context(const WindowRef &aWindowRef) :
	mWindowRef(aWindowRef)
{
	if (!createGlContext())
	{
		PostQuitMessage(0);
	}
}

Context::~Context()
{
	releaseGlContext();
}

bool Context::createGlContext()
{
	/*
	The important things to note here are:
	dwFlags: enables OpenGL support and double buffering
	cColorBits: sets the precision of the color buffer
	cDepthBits: sets the precision of the depth buffer
	*/
	static PIXELFORMATDESCRIPTOR pfd;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 16;
	pfd.cRedBits = 0;
	pfd.cRedShift = 0;
	pfd.cGreenBits = 0;
	pfd.cGreenShift = 0;
	pfd.cBlueBits = 0;
	pfd.cBlueShift = 0;
	pfd.cAlphaBits = 0;
	pfd.cAlphaShift = 0;
	pfd.cAccumRedBits = 0;
	pfd.cAccumGreenBits = 0;
	pfd.cAccumBlueBits = 0;
	pfd.cAccumAlphaBits = 0;
	pfd.cDepthBits = 16;
	pfd.cStencilBits = 0;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;

	// get the device context associated with this window
	mDc = GetDC(mWindowRef->getHandle());

	// request a pixel format
	int pixelFormat = ChoosePixelFormat(mDc, &pfd);

	if (!pixelFormat)
	{
		MessageBox(0, TEXT("Can't find PixelFormat"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	if (!SetPixelFormat(mDc, pixelFormat, &pfd))
	{
		MessageBox(0, TEXT("Can't set PixelFormat"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	// use the device context to create a rendering context
	mGlrc = wglCreateContext(mDc);

	if (!mGlrc)
	{
		MessageBox(0, TEXT("Can't create GL rendering context"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	if (!wglMakeCurrent(mDc, mGlrc))
	{
		MessageBox(0, TEXT("Can't activate GL rendering context"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	// initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
	glGetError();

	return true;
}

void Context::releaseGlContext()
{
	ChangeDisplaySettings(NULL, 0);		// restore the original display settings
	wglMakeCurrent(mDc, NULL);			// deselect the rendering context
	wglDeleteContext(mGlrc);			// delete the rendering context
	ReleaseDC(mWindowRef->getHandle(), mDc);
}

void Context::resizeGlContext(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
}