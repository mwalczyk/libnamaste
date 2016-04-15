#pragma once

#include "../Namaste/Platform.h"

class GlslProgram;
using GlslProgramRef = std::shared_ptr<GlslProgram>;

class GlslProgram
{
public:
	GlslProgram();
	~GlslProgram();

	static inline GlslProgramRef create()
	{
		return GlslProgramRef(new GlslProgram);
	}

	void compile(const GLchar *vertSrc, const GLchar *fragSrc, const GLchar *geomSrc = nullptr);
	void bind() const;
	void unbind() const;
	void setUniform1i(const std::string &uniformName, GLint v) const;
	void setUniform1f(const std::string &uniformName, GLfloat v) const;
	void setUniform2f(const std::string &uniformName, GLfloat v1, GLfloat v2) const;
	void setUniform2f(const std::string &uniformName, const glm::vec2 &v) const;
	void setUniform3f(const std::string &uniformName, GLfloat v1, GLfloat v2, GLfloat v3) const;
	void setUniform3f(const std::string &uniformName, const glm::vec3 &v) const;
	void setUniform4f(const std::string &uniformName, GLfloat v1, GLfloat v2, GLfloat v3, GLfloat v4) const;
	void setUniform4f(const std::string &uniformName, const glm::vec4 &v) const;
	void setUniform4x4Matrix(const std::string &uniformName, const glm::mat4 &matrix) const;

	GLuint programId;
private:
	void checkCompileErrors(GLuint objectId, const std::string &type);
};