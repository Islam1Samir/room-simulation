#include "Table.h"
#include <glm\gtx\transform.hpp>

Table::Table(void)
{
}


Table::~Table(void)
{
}
void Table::Initialize()
{
	leg=Tr();
	leg.Initialize();
	mSquare = Model();
	mSquare.VertexData.push_back(glm::vec3(-1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(1.0f, -1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3( 1.0f,  1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3( -1.0f,  1.0f, 0.0f));
	//we want a gray cube cube.
	mSquare.ColorData.push_back(glm::vec3(0.0f, 0.5f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.5f, 0.0f));
	mSquare.ColorData.push_back(glm::vec3(0.5f, 0.5f, 1.0f));
	mSquare.ColorData.push_back(glm::vec3(1.0f, 0.5f, 0.5f));
	//first.riangle.
	mSquare.IndicesData.push_back(0);
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(3);
	//secon.triangle.
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(2);
	mSquare.IndicesData.push_back(3);
	glm::vec3 mySquareNormal = glm::vec3(0.0, 0.0, -1.0);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.NormalsData.push_back(mySquareNormal);
	mSquare.UVData.push_back(glm::vec2(0.0f, 0.0f));
	mSquare.UVData.push_back(glm::vec2(1.0f, 0.0f));
	mSquare.UVData.push_back(glm::vec2(1.0f, 1.0f));
	mSquare.UVData.push_back(glm::vec2(0.0f, 1.0f));
	mSquare.Initialize();



	int numberOfFaces = 6;
	mFacesModelMatrices.resize(numberOfFaces);
	
	//bottom
	mFacesModelMatrices[0] = glm::translate(0.0f,0.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//top
	mFacesModelMatrices[1] = glm::translate(0.0f,0.25f,0.0f)*glm::rotate(90.0f,glm::vec3(1.0f,0.0f,0.0f));
	//front
	mFacesModelMatrices[2] =glm::scale(1.0f,0.125f,1.0f)* glm::translate(0.0f,1.0f,1.0f)*glm::rotate(180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	//back
	mFacesModelMatrices[3] = glm::scale(1.0f,0.125f,1.0f)*glm::translate(0.0f,1.0f,-1.0f);
	//left
	mFacesModelMatrices[4] = glm::scale(1.0f,0.125f,1.0f)*glm::translate(-1.0f,1.0f,0.0f)*glm::rotate(90.0f,glm::vec3(0.0f,1.0f,0.0f));
	//right
	mFacesModelMatrices[5] = glm::scale(1.0f,0.125f,1.0f)*glm::translate(1.0f,1.0f,0.0f)*glm::rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));

	//this transformation is applied on the whole cube!!!
	TableModelMatrix = glm::translate(0.0f,0.75f,0.0f)*glm::scale(0.5f,0.5f,0.5f);
}

void Table::Draw(GLuint mvpUniformMatrixID,glm::mat4 VP,GLuint ModelMatrixID, glm::mat4 trans)
{

	for (int i = 0; i < mFacesModelMatrices.size(); i++)
	{
		/*if(i==2||i==4||i==3||i==5){
			glm::mat4	RoomModelMatrix22 = glm::translate(0.0f,1.50f,0.0f)*glm::scale(1.0f,0.25f,1.0f)*glm::scale(0.5f,0.5f,0.5f);
		glm::mat4 mvp = VP * RoomModelMatrix22* mFacesModelMatrices[i];
		glUniformMatrix4fv(mvpUniformMatrixID, 1, GL_FALSE, &mvp[0][0]);
		mSquare.Draw();
		continue;
		}*/
		glm::mat4 mvp = VP*trans * TableModelMatrix * mFacesModelMatrices[i];
		glm::mat4 mvpn= trans*TableModelMatrix * mFacesModelMatrices[i];
		glUniformMatrix4fv(mvpUniformMatrixID, 1, GL_FALSE, &mvp[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &mvpn[0][0]);
		mSquare.Draw();
	}
	glm::mat4 mvp = VP* glm::translate(0.4f,0.0f,-0.4f) ;
		//glUniformMatrix4fv(mvpUniformMatrixID, 1, GL_FALSE, &mvp[0][0]);
		leg.Draw( mvpUniformMatrixID, VP,ModelMatrixID, trans*glm::translate(0.4f, 0.0f, -0.4f));
		mvp = VP* glm::translate(-0.4f,0.0f,-0.4f) ;
		leg.Draw( mvpUniformMatrixID, VP,ModelMatrixID, trans*glm::translate(-0.4f, 0.0f, -0.4f));
		mvp = VP* glm::translate(0.4f,0.0f,0.4f) ;
		leg.Draw( mvpUniformMatrixID, VP,ModelMatrixID, trans*glm::translate(0.4f, 0.0f, 0.4f));
		mvp = VP* glm::translate(-0.4f,0.0f,0.4f) ;
		leg.Draw( mvpUniformMatrixID, VP,ModelMatrixID, trans*glm::translate(-0.4f, 0.0f, 0.4f));
}
