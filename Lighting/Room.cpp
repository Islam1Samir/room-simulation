#include "Room.h"
#include <glm\gtx\transform.hpp>

Room::Room(void)
{
}


Room::~Room(void)
{
}
void Room::Initialize()
{
	door=Tr();
	door.Initialize();
	mSquare = Model();
	mSquare.VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	//we want a gray cube cube.
	mSquare.ColorData.push_back(glm::vec3(1.0f, 1.0f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(0.0f, 1.0f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(0.0f, 1.0f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.0f, 0.5f));
	
	//first.riangle.
	mSquare.IndicesData.push_back(0);
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(3);
	//secon.triangle.
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(2);
	mSquare.IndicesData.push_back(3);
	//squareNormal = 
glm::vec3 mySquareNormal = glm::vec3(0.0, 0.0, 1.0);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	//mSquare.NormalsData.clear();

	mSquare.UVData.push_back(glm::vec2(0.0f,0.0f));
	mSquare.UVData.push_back(glm::vec2(1.0f,0.0f));
	mSquare.UVData.push_back(glm::vec2(1.0f,1.0f));
	mSquare.UVData.push_back(glm::vec2(0.0f,1.0f));
	mSquare.Initialize();



	int numberOfFaces = 6;
	mFacesModelMatrices.resize(numberOfFaces);
	
	//bottom
	mFacesModelMatrices[0] = glm::translate(0.0f,0.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//top
	mFacesModelMatrices[1] = glm::translate(0.0f,1.0f,0.0f)*glm::rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//front
	mFacesModelMatrices[2] = glm::translate(0.0f,0.0f,1.0f)*glm::rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//back
	mFacesModelMatrices[3] = glm::translate(0.0f,0.0f,-1.0f);
	//left
	mFacesModelMatrices[4] = glm::translate(-1.0f,0.0f,0.0f)*glm::rotate(90.0f,glm::vec3(0.0f,1.0f,0.0f));
	//right
	mFacesModelMatrices[5] = glm::translate(1.0f,0.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));

	//this transformation is applied on the whole cube!!!
	RoomModelMatrix = glm::scale(2.0f,2.0f,2.0f);
}

void Room::Draw(GLuint mvpUniformMatrixID,glm::mat4 VP,GLuint ModelMatrixID,int skip)
{

	for (int i = 0; i < mFacesModelMatrices.size(); i++)
	{
		if(i==skip)
			continue;
		if(i==2||i==3||i==4||i==5){
			glm::mat4	RoomModelMatrix22 = glm::translate(0.0f,1.0f,0.0f)*glm::scale(2.0f,1.0f,2.0f);
		glm::mat4 mvp = VP * RoomModelMatrix22* mFacesModelMatrices[i];
		glm::mat4 mvpn=RoomModelMatrix22 * mFacesModelMatrices[i];
	
			
		//	mvpn=glm::rotate(180.0f,glm::vec3(0.0f,1.0f,0.0f))*mvpn;
		glUniformMatrix4fv(mvpUniformMatrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &mvpn[0][0]);
		mSquare.Draw();
		continue;
		}
		
		glm::mat4 mvp = VP * RoomModelMatrix * mFacesModelMatrices[i];
		glm::mat4 mvpn=RoomModelMatrix * mFacesModelMatrices[i];
		
		glUniformMatrix4fv(mvpUniformMatrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &mvpn[0][0]);
		mSquare.Draw();
	}
	
}
