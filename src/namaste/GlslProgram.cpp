#include "namaste\GlslProgram.h"

GlslProgram::GlslProgram()
{
}

GlslProgram::~GlslProgram()
{
}

void GlslProgram::compile(const GLchar *vertSrc, const GLchar *fragSrc, const GLchar *geomSrc)
{
	GLuint vertId;
	GLuint fragId;
	GLuint geomId;

	// Vertex shader
	vertId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertId, 1, &vertSrc, NULL);
	glCompileShader(vertId);
	checkCompileErrors(vertId, "VERTEX");

	// Fragment shader
	fragId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragId, 1, &fragSrc, NULL);
	glCompileShader(fragId);
	checkCompileErrors(fragId, "FRAGMENT");

	// Geometry shader source code is optional
	if (geomSrc != nullptr)
	{
		geomId = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geomId, 1, &geomSrc, NULL);
		glCompileShader(geomId);
		checkCompileErrors(geomId, "GEOMETRY");
	}

	programId = glCreateProgram();
	glAttachShader(programId, vertId);
	glAttachShader(programId, fragId);
	if (geomSrc != nullptr)
	{
		glAttachShader(programId, geomId);
	}

	glLinkProgram(programId);
	checkCompileErrors(programId, "PROGRAM");

	// Delete the shaders as they've already been linked into the program object
	glDeleteShader(vertId);
	glDeleteShader(fragId);
	if (geomSrc != nullptr)
	{
		glDeleteShader(geomId);
	}
}

void GlslProgram::bind() const
{
	glUseProgram(programId);
}

void GlslProgram::unbind() const
{
	glUseProgram(0);
}

void GlslProgram::setUniform1i(const std::string &uniformName, GLint v) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform1i(uniformLocation, v);
}

void GlslProgram::setUniform1f(const std::string &uniformName, GLfloat v) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform1f(uniformLocation, v);
}

void GlslProgram::setUniform2f(const std::string &uniformName, GLfloat v1, GLfloat v2) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform2f(uniformLocation, v1, v2);
}

void GlslProgram::setUniform2f(const std::string &uniformName, const glm::vec2 &v) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform2f(uniformLocation, v.x, v.y);
}

void GlslProgram::setUniform3f(const std::string &uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform3f(uniformLocation, v1, v2, v3);
}

void GlslProgram::setUniform3f(const std::string &uniformName, const glm::vec3 &v) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform3f(uniformLocation, v.x, v.y, v.z);
}

void GlslProgram::setUniform4f(const std::string &uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform4f(uniformLocation, v1, v2, v3, v4);
}

void GlslProgram::setUniform4f(const std::string &uniformName, const glm::vec4 &v) const
{
	GLint uniformLocation = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLocation != -1) glUniform4f(uniformLocation, v.x, v.y, v.z, v.w);
}

void GlslProgram::setUniform4x4Matrix(const std::string &uniformName, const glm::mat4 &matrix) const
{
	/*
	* The parameters of glUniformMatrix4fv are as follows:
	* 1) The uniform location
	* 2) The # of matrices we want to send
	* 3) Should the matrix be transposed?
	* 4) The actual matrix data, transformed into an OpenGL-ready format
	*/
	GLuint uniformLoc = glGetUniformLocation(programId, uniformName.c_str());
	if (uniformLoc != -1) glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GlslProgram::checkCompileErrors(GLuint objectId, const std::string &type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(objectId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(objectId, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n"
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(objectId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(objectId, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n"
				<< std::endl;
		}
	}
}