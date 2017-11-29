#include "namaste/Window.h"

const wchar_t *WINDOW_CLASS_NAME = TEXT("NamasteWinClass");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	/*
	This is where all of the messages that are sent to our window get processed. It is called once
	for each messsage. HWND is the handle to the window. In a multi-window application, this parameter
	will vary for each window (even if they all use the same window class).
	*/
	switch (msg)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_SPACE:
		case VK_RETURN:
			// don't call PostQuitMessage(0) here because that should only happen in one place (WM_CLOSE)
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		}
		break;
	case WM_QUIT:
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

Window::Window(HINSTANCE hInstance, int nCmdShow, bool showConsole) :
	mInstance(hInstance)
{
	registerWindow();

	if (showConsole)
	{
		createConsole();
	}

	createWindow(nCmdShow);
}

Window::~Window()
{
	DestroyWindow(mWnd);
}

int Window::registerWindow()
{
	WNDCLASSEX wc;
	MSG msg;

	wc.cbSize = sizeof(WNDCLASSEX);						// size of the structure
	wc.style = 0;										// class styles, usually 0
	wc.lpfnWndProc = WndProc;							// pointer to the window procedure for this class
	wc.cbClsExtra = 0;									// amount of extra data allocated for this class, usually 0
	wc.cbWndExtra = 0;									// amount of extra data allocated in memory per window of this type, usually 0
	wc.hInstance = mInstance;							// handle to the application instance (from WinMain)
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);			// large icon that is displayed when the user presses alt+tab
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// cursor that will be displayed over the window
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);		// background brush to set the color of the window
	wc.lpszMenuName = NULL;								// name of the menu resource to use with windows of this class
	wc.lpszClassName = TEXT("NamasteWinClass");			// name to identify this class
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
}

int Window::createWindow(int nCmdShow)
{
	/*
	The parameters of CreateWindowEx are as follows:
	1) the extended window style
	2) the class name
	3) the window title
	4) the window style
	5, 6, 7, 8) the x and y coordinates of the top left corner of the window followed by the width and height of the window
	9, 10, 11, 12) the parent window handle, the menu handle, the application instance handle, and a pointer to window creation data
	*/
	mWnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("NamasteWinClass"), TEXT("Namaste"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, mInstance, NULL);

	if (mWnd == NULL)
	{
		MessageBox(NULL, TEXT("Window Creation Failed!"), TEXT("Error!"), MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	// update the window 
	ShowWindow(mWnd, nCmdShow);
	UpdateWindow(mWnd);
}

void Window::createConsole()
{
	/*
	Clear the error state for each of the C++ standard stream objects. We need to do this, as
	attempts to access the standard streams before they refer to a valid target will cause the
	iostream objects to enter an error state. In versions of Visual Studio after 2005, this seems
	to always occur during startup regardless of whether anything has been read from or written to
	the console or not.
	*/
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	std::wcout.clear();
	std::cout.clear();
	std::wcerr.clear();
	std::cerr.clear();
	std::wcin.clear();
	std::cin.clear();
}

