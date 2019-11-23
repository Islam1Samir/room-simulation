#pragma once

#include "Model\Model.h"
#include "Tr.h"
class Room
{
	Model mSquare;
	Tr door;
	std::vector<glm::mat4> mFacesModelMatrices;
public:
	Room(void);
	~Room(void);

	glm::mat4 RoomModelMatrix;
	void Initialize();
	void Draw(GLuint mvpUniformMatrixID,glm::mat4 VP,GLuint ModelMatrixID,int cam);
	void Cleanup();
};

