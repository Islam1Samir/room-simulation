#ifndef Cube_h__
#define Cube_h__

#include "Model\Model.h"
class Cube
{
	Model mSquare;
	std::vector<glm::mat4> mFacesModelMatrices;
public:
	Cube(void);
	~Cube(void);

	glm::mat4 CubeModelMatrix;
	void Initialize();
	//void trans(int x,glm::vec3 scale,glm::vec3 translate )
	void Draw(GLuint mvpUniformMatrixID,glm::mat4 VP);
	void Cleanup();
};

#endif // Cube_h__
