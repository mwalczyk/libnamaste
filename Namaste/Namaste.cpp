#include "stdafx.h"

#include "Platform.h"

// references: 
// setting up a basic window: http://www.winprog.org/tutorial/simple_window.html
// adding an OpenGL context: http://www.alsprogrammingresource.com/win32_tut06.html
// reading application time: http://advancedcppwithexamples.blogspot.com/2009/08/measuring-elapsed-time-in-c-using_22.html

HWND gWnd;			// window handle
HDC gDc;			// device context
HGLRC gGlrc;		// rendering context
RECT screenRect;
RECT clientRect;

bool CreateGlContext(HWND hWnd, HDC &hDc, HGLRC &hGlrc)
{
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
	pfd.cDepthBits = 0;
	pfd.cStencilBits = 0;
	pfd.cAuxBuffers = 0;
	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.bReserved = 0;
	pfd.dwLayerMask = 0;
	pfd.dwVisibleMask = 0;
	pfd.dwDamageMask = 0;

	hDc = GetDC(hWnd);

	int pixelFormat = ChoosePixelFormat(hDc, &pfd);

	if (!pixelFormat)
	{
		MessageBox(0, TEXT("Can't find PixelFormat"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	if (!SetPixelFormat(hDc, pixelFormat, &pfd))
	{
		MessageBox(0, TEXT("Can't set PixelFormat"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	hGlrc = wglCreateContext(hDc);

	if (!hGlrc)
	{
		MessageBox(0, TEXT("Can't create GL rendering context"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	if (!wglMakeCurrent(hDc, hGlrc))
	{
		MessageBox(0, TEXT("Can't activate GL rendering context"), TEXT("Error"), MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}

void ReleaseGlContext(HWND hWnd, HDC &hDc, HGLRC &hGlrc)
{
	ChangeDisplaySettings(NULL, 0);
	wglMakeCurrent(hDc, NULL);
	wglDeleteContext(hGlrc);
	ReleaseDC(hWnd, hDc);
}

/*
This is where all of the messages that are sent to our window get processed. It is called once
for each messsage. HWND is the handle to the window. In a multi-window application, this parameter
will vary for each window (even if they all use the same window class). 
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		if (CreateGlContext(hWnd, gDc, gGlrc))
		{
			GetClientRect(hWnd, &clientRect);
			//InitGL(clientRect.right, clientRect.bottom);
		}
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &clientRect);
		// ResizeGlScene(clientRect.right, clientRect.bottom);
		break;
	case WM_QUIT:
	case WM_CLOSE:
		ReleaseGlContext(gWnd, gDc, gGlrc);
		DestroyWindow(gWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	MSG msg;

	static const wchar_t *WINDOW_CLASS_NAME = TEXT("NamasteWinClass");

	wc.cbSize = sizeof(WNDCLASSEX);						// size of the structure
	wc.style = 0;										// class styles, usually 0
	wc.lpfnWndProc = WndProc;							// pointer to the window procedure for this class
	wc.cbClsExtra = 0;									// amount of extra data allocated for this class, usually 0
	wc.cbWndExtra = 0;									// amount of extra data allocated in memory per window of this type, usually 0
	wc.hInstance = hInstance;							// handle to the application instance (from WinMain)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// large icon that is displayed when the user presses alt+tab
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// cursor that will be displayed over the window
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// background brush to set the color of the window
	wc.lpszMenuName = NULL;								// name of the menu resource to use with windows of this class
	wc.lpszClassName = WINDOW_CLASS_NAME;				// name to identify this class
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);		// small icon that is displayed in the top left corner of the window

	/*
	A window class stores information about a window, including its window procedure. The window procedure
	controls the window, its icons, and its background color. This way, we can register a class once, and 
	create as many windows as we want from that class without having to repeatedly specify those attributes.
	*/
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, TEXT("Window Registration Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	/*
	The parameters of CreateWindowEx are as follows:
	1) the extended window style
	2) the class name
	3) the window title
	4) the window style
	5, 6, 7, 8) the x and y coordinates of the top left corner of the window followed by the width and height of the window
	9, 10, 11, 12) the parent window handle, the menu handle, the application instance handle, and a pointer to window creation data
	*/
	gWnd = CreateWindowEx(WS_EX_CLIENTEDGE, WINDOW_CLASS_NAME, TEXT("Namaste"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);

	if (gWnd == NULL)
	{
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// update the window 
	ShowWindow(gWnd, nCmdShow);
	UpdateWindow(gWnd);
	timeBeginPeriod(1);

	while (true) 
	{
		/*
		Any time the user moves the mouse, types on the keyboard, clicks on a menu item, etc. messages are generated
		by the system and entered into the message queue. By calling GetMessage, we are requesting the next available
		message. TranslateMessage() does some additional processing on keyboard events. DispatchMessage() sends the
		message out to the window that the message was sent to.
		*/
		while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				return msg.wParam;
			}
		}

		DWORD startTime = timeGetTime();
		float ypos = sinf(startTime * 0.001f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
		glBegin(GL_TRIANGLES);

		// vertex 1
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, 0.0f);

		// vertex 2
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.5f, 0.0f);

		// vertex 3
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.2f * ypos, 0.5f);

		glEnd();

		glFinish();
		SwapBuffers(gDc);
	}
	

	return msg.wParam;
}