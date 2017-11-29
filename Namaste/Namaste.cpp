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

	std::vector<GLfloat> mColors;
};

void MyApp::setup()
{
	//mGlslProgram = ResourceManager::loadShader("C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.vert", "C:\\Users\\michael.walczyk\\Documents\\Namaste\\resources\\basic.frag");

	//std::vector<GLfloat> verts {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f,  0.5f, 0.0f
	//};

	//mVaoId;
	////glCreateVertexArrays(1, &mVaoId);
	//glGenVertexArrays(1, &mVaoId);
	//glBindVertexArray(mVaoId);

	//BufferRef vbo = Buffer::create(GL_ARRAY_BUFFER, verts);
	//vbo->bind();

	//// attribute 0 -> position
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//glEnableVertexAttribArray(0);

	//// unbind vao
	//glBindVertexArray(0);

	//// unbind vbo
	//vbo->unbind();
	std::cout << "OpenGL: " << getGlVersion() << "\n";
	std::cout << "GLSL: " << getGlslVersion() << "\n";

	const GLchar vertSrc[] =
	{
		"#version 420 core													\n"
		"layout (location = 0) in vec4 color;								\n"
		"out vec4 vColor;													\n"
		"void main()														\n"
		"{																	\n"
		"	const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0),	\n"
		"									 vec4(-0.25, -0.25, 0.5, 1.0),	\n"
		"									 vec4(0.25, 0.25, 0.5, 1.0));	\n"
		"	gl_Position = vertices[gl_VertexID];							\n"
		"	vColor = color;													\n"
		"}																	\n"
	};

	const GLchar fragSrc[] =
	{
		"#version 420 core													\n"
		"in vec4 vColor;													\n"
		"out vec4 oColor;													\n"
		"void main()														\n"
		"{																	\n"
		"	oColor = vColor;												\n"
		"}																	\n"
	};

	mGlslProgram.compile(vertSrc, fragSrc);
}

void MyApp::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	std::vector<GLfloat> colors = { sinf(getElapsedSeconds() * 0.001) * 0.5f + 0.5f,
								    cosf(getElapsedSeconds() * 0.001) * 0.5f + 0.5f,
								    0.0f, 1.0f };
	mGlslProgram.bind();
	
	glVertexAttrib4fv(0, colors.data());
	glDrawArrays(GL_TRIANGLES, 0, 3);\

	mGlslProgram.unbind();
}

DECLARE_MAIN(MyApp)