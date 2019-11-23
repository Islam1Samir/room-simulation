#pragma once
#include "Model\Model.h"
#include "Tr.h"
class Table
{
	Model mSquare;
	Tr leg;
	std::vector<glm::mat4> mFacesModelMatrices;
public:
	Table(void);
	~Table(void);
	glm::mat4 TableModelMatrix;
	void Initialize();
	void Draw(GLuint mvpUniformMatrixID,glm::mat4 VP,GLuint ModelMatrixID, glm::mat4 trans);
	void Cleanup();
};

