#pragma once

#include "Platform.h"

class Window;
using WindowRef = std::shared_ptr<Window>;

class Window
{

public:

	Window(HINSTANCE hInstance, int nCmdShow, bool showConsole = true);
	~Window();

	static inline WindowRef create(HINSTANCE hInstance, int nCmdShow, bool showConsole = true)
	{
		return WindowRef(new Window(hInstance, nCmdShow, showConsole));
	}

	HWND getHandle() const { return mWnd; };

private:

	int registerWindow();
	int createWindow(int nCmdShow);
	void createConsole();

	static const wchar_t *WINDOW_CLASS_NAME;

	HINSTANCE mInstance;
	HWND mWnd;				// window handle
	HDC mDc;				// device context - an interface to the hardware
	HGLRC mGlrc;			// rendering context - used when drawing to the output device

};