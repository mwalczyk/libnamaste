#include "namaste/Platform.h"
#include "namaste/GlslProgram.h"
#include "namaste/ResourceManager.h"
#include "namaste/Window.h"
#include "namaste/Context.h"

GlslProgram prog;
GLuint vaoID;

void setup()
{
	prog = ResourceManager::loadShader("C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.vert", "C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.frag");
	
	std::vector<GLfloat> verts {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

    vaoID;

	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);

		BufferRef vbo = Buffer::create(GL_ARRAY_BUFFER, verts);
		vbo->bind();

		// attribute 0 -> position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	vbo->unbind();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR lpCmdLine, int nCmdShow)
{
	WindowRef win = Window::create(hInstance, nCmdShow);
	ContextRef con = Context::create(win);

	MSG msg;

	setup();

	timeBeginPeriod(1);

	while (true) 
	{
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
			else
			{
				return msg.wParam;
			}
		}

		DWORD startTime = timeGetTime();
		float ypos = sinf(startTime * 0.001f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

		prog.bind();
		
		prog.setUniform1f("uTime", startTime * 0.001f);
		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		prog.unbind();

		glFinish();
		SwapBuffers(con->getDeviceContext());
	}
	
	return msg.wParam;
}