#pragma once
#include "Model\Model.h"
class Tr
{
	Model mSquare;
	std::vector<glm::mat4> mFacesModelMatrices;
public:
	Tr(void);
	~Tr(void);
	glm::mat4 TableModelMatrix;
	void Initialize();
	void Draw(GLuint mvpUniformMatrixID,glm::mat4 VP,GLuint ModelMatrixID, glm::mat4 trans);
	void Cleanup();
};

