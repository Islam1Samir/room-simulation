#pragma once
#include "gl/glew.h"
#include "glm/glm.hpp"
#include "Shaders/shader.hpp"


class ShaderProgram
{
	public:
	GLuint programID;

	GLuint modelMatrixID;
	GLuint vpMatrixID;
	GLuint clipID;
	ShaderProgram();
	~ShaderProgram();

	void BindModelMatrix(GLfloat* value);
	void BindClipPlane(GLfloat* value);
	void BindVPMatrix(GLfloat* value);
	
	//calls glUseProgram.
	void UseProgram();
	//load shaders from files.
	void LoadProgram();
	void CleanUp();
};

