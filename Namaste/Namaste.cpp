#include "namaste/Platform.h"
#include "namaste/GlslProgram.h"
#include "namaste/ResourceManager.h"
#include "namaste/Window.h"
#include "namaste/Context.h"
#include "namaste/App.h"

class MyApp : public App
{
	void setup() override;
	void draw() override;

	GlslProgram mGlslProgram;
	GLuint mVaoId;
};

void MyApp::setup()
{
	mGlslProgram = ResourceManager::loadShader("C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.vert", "C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.frag");

	std::vector<GLfloat> verts {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	mVaoId;

	glGenVertexArrays(1, &mVaoId);
	glBindVertexArray(mVaoId);

	BufferRef vbo = Buffer::create(GL_ARRAY_BUFFER, verts);
	vbo->bind();

	// attribute 0 -> position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// unbind vao
	glBindVertexArray(0);

	// unbind vbo
	vbo->unbind();
}

void MyApp::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	mGlslProgram.bind();
	mGlslProgram.setUniform1f("uTime", getElapsedSeconds() * 0.001f);

	glBindVertexArray(mVaoId);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	mGlslProgram.unbind();
}

DECLARE_MAIN(MyApp)