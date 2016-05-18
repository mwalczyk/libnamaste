#pragma once

#include "namaste/Window.h"
#include "namaste/Context.h"

class App
{
public:
	virtual void run(App *app)
	{
		app->setup();

		do
		{
			app->draw();

			MSG msg;

			/*
			Any time the user moves the mouse, types on the keyboard, clicks on a menu item, etc. messages are generated
			by the system and entered into the message queue. By calling GetMessage, we are requesting the next available
			message. TranslateMessage() does some additional processing on keyboard events. DispatchMessage() sends the
			message out to the window that the message was sent to.
			*/
			while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))	// checks if any messages are available but does not remove them from the queue
			{
				if (GetMessage(&msg, NULL, 0, 0))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			// clear command buffer and swap 
			glFinish();
			SwapBuffers(mContext->getDeviceContext());

		} while (true);

		app->exit();
	}
	virtual void setup() {}
	virtual void draw() {}
	virtual void exit() {}

	WindowRef mWindow;
	ContextRef mContext;
};

DWORD getElapsedSeconds()
{
	return timeGetTime();
}

#define DECLARE_MAIN(APP)\
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR lpCmdLine, int nCmdShow) \
{ \
	WindowRef win = Window::create(hInstance, nCmdShow); \
	ContextRef con = Context::create(win); \
	App *app = new APP; \
	app->mWindow = win; \
	app->mContext = con; \
	app->run(app); \
	return 0; \
}
