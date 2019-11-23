#ifndef Renderer_h__
#define Renderer_h__

#include <gl/glew.h>
#include <gl/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Model3D.h"
#include"texture.h"
#include "Shaders/shader.hpp"
#include "Model/Model.h"
#include "EulerCamera/EulerCamera.h"
#include "Cube/Cube.h"
#include "Room.h"
#include "Table.h"
#include "Tr.h"
#include "ShaderProgram.h"

class Renderer
{

	
		GLuint mRenderingModeID;
	
    GLuint programID;

	glm::vec3 Dir;
	GLuint DirID;
	// Transformation
	GLuint MatrixID;
	GLuint ModelMatrixID;
	GLuint AmbientLightID;
	GLuint LightPositionID;
	GLuint EyePositionID;
	ShaderProgram shader;
	std::unique_ptr<Model3D> radio;
	std::unique_ptr<Room> myCube;
	
	std::unique_ptr<Table> myTable;
	std::unique_ptr<EulerCamera> myCamera;
	std::unique_ptr<EulerCamera> myCamera2;
	std::unique_ptr<Tr> black;
	std::unique_ptr<Tr> door;
	std::unique_ptr<Texture> mTexture1;
	std::unique_ptr<Texture> mTexture2;
	std::unique_ptr<Texture> mTexture3;
	std::unique_ptr<Texture> mTexture4;
	std::unique_ptr<Texture> mTexture5;

	std::unique_ptr<Cube> lSquare;
	glm::mat4 doormvp; 
	float m;
	float n;
	bool dooropened;
	int cam;
	glm::vec3 ambientLight;
	glm::vec3 lightPosition;

public:
    Renderer();
    ~Renderer();
    
    void Initialize();
    void Draw();
	bool lLoadingmenu();
	void HandleKeyboardInput(int key);
	void HandleMouse(double deltaX,double deltaY);
	void Update(double deltaTime);
    void Cleanup();
};

#endif // Renderer_h__

