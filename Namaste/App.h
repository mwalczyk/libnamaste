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
		} while (true);

		app->exit();
	}

	virtual void setup();
	virtual void draw();
	virtual void exit();
private:
	WindowRef mWindow;
	ContextRef mContext;
};

#define DECLARE_MAIN(AppDerived)										\  
int WINAPI WinMain(HINSTANCE hInstance,						\
	HINSTANCE hPrevious,									\
	LPSTR lpCmdLine,										\
	int nCmdShow)											\
{															\
	WindowRef win = Window::create(hInstance, nCmdShow);	\
	ContextRef con = Context::create(win);					\
	App *app = static_cast<App*>(new AppDerived);			\
    app->run(app);											\
    delete app;												\     
    return 0;												\    
}															