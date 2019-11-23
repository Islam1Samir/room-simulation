#include "Renderer.h"
#include "windows.h"
#include "mmsystem.h"
//#include "boost\thread.hpp"
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

Renderer::Renderer()
{
    
}

Renderer::~Renderer()
{
    Cleanup();
}

void Renderer::Initialize()
{
	radio= std::unique_ptr<Model3D>(new Model3D());
	radio->LoadFromFile("data/Gramophone N090913.3DS",true);
	//radio->LoadFromFile("data\models\ra\graphaphone.3DS", true);
	radio->Initialize();
	black = std::unique_ptr<Tr>(new Tr());
	black->Initialize();

	// PlaySound("starwars.wav", NULL, SND_FILENAME|SND_LOOP);
	cam=-1;
	m=0;
	dooropened=0;
	//myCamera = std::unique_ptr<FPCamera>(new FPCamera());
	myCamera = std::unique_ptr<EulerCamera>(new EulerCamera());
	myCamera2 = std::unique_ptr<EulerCamera>(new EulerCamera());

	myTable=std::unique_ptr<Table>(new Table());
	myTable->Initialize();

	//////////////////////////////////////////////////////////////////////////
	myCube = std::unique_ptr<Room>(new Room());
	myCube->Initialize();
	
	//////////////////////////////////////////////////////////////////////////
	
	//////////////////////////////////////////
	door =std::unique_ptr<Tr>(new Tr());
	door->Initialize();

	mTexture1 = std::unique_ptr<Texture>(new Texture("door.jpg",0));
	mTexture2 = std::unique_ptr<Texture>(new Texture("wood.jpg", 1));
	mTexture3 = std::unique_ptr<Texture>(new Texture("tab.jpeg", 2));
	mTexture4 = std::unique_ptr<Texture>(new Texture("da.jpg", 3));
	mTexture5 = std::unique_ptr<Texture>(new Texture("black.jpg", 3));



	// Create and compile our GLSL program from the shaders
	programID = LoadShaders( "SimpleTransformWithColor.vertexshader", "MultiColor.fragmentshader" );
	mRenderingModeID = glGetUniformLocation(programID,"RenderingMode");
	MatrixID = glGetUniformLocation(programID, "MVP");
	ModelMatrixID = glGetUniformLocation(programID, "ModelMatrix");
	// Use our shader
	glUseProgram(programID);
	//shader.LoadProgram();
	//////////////////////////////////////////////////////////////////////////
	// Configure the light.
	//setup the light position.
	DirID = glGetUniformLocation(programID, "lookat");
	LightPositionID = glGetUniformLocation(programID,"LightPosition_worldspace");
	lightPosition = glm::vec3(0.0,1.0,0.5);
	glUniform3fv(LightPositionID,1, &lightPosition[0]);
	//setup the ambient light component.
	AmbientLightID = glGetUniformLocation(programID,"ambientLight");
	ambientLight = glm::vec3(0.1,0.1,0.1);
	glUniform3fv(AmbientLightID,1, &ambientLight[0]);
	//setup the eye position.
	EyePositionID = glGetUniformLocation(programID,"EyePosition_worldspace");
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,200.0f);
	myCamera2->SetPerspectiveProjection(45.0f,4.0f/3.0f,0.1f,100.0f);
	n = 0;
	// View matrix : 
	myCamera->Reset(0.0,1.0,2.0,
					0,1,0,
					0,1,0);
	myCamera2->Reset(0.0,5.0,3.0,
					0,0,0,
					0,1,0);
	myCamera2->mAngleY=-0.9;
	//send the eye position to the shaders.
	
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	//////////////////////////////////////////////////////////////////////////
	//doormvp = glm::translate(-0.5f,0.0f,0.0f)*glm::scale(5.0f,2.0f,0.5f);
		//PlaySound(TEXT("skoon.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
		glUniform1i(mRenderingModeID, 1);
		
}

void Renderer::Draw()
{
 
	
	Dir = myCamera->GetLookDirection();
	glUniform3fv(DirID, 1, &Dir[0]);
	glUniform3fv(LightPositionID, 1, &myCamera->GetEyePosition()[0]);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
	glm::mat4 VP;
	if(cam==-1)
		 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
		//1st triangle
	else
		 VP = myCamera2->GetProjectionMatrix() * myCamera2->GetViewMatrix();
	//	doormvp = VP *glm::scale(6.0f,2.0f,0.5f)*glm::translate(0.2f,0.0f,-4.0f);
	
	//mRenderingMode = RenderingMode::TEXTURE_ONLY;
		
	
	
	mTexture1->Bind();
		glm::mat4 VPdoor=glm::translate(1.8f,0.0f,-2.0f)*doormvp;
		door->Draw(MatrixID,VP,ModelMatrixID, VPdoor);

		mTexture5->Bind();
		glm::mat4 VPblack = glm::translate(1.3f, 0.0f, -2.01f)*glm::scale(5.0f, 2.0f, 0.5f);
		black->Draw(MatrixID, VP, ModelMatrixID, VPblack);
	

	mTexture2->Bind();
	myCube->Draw(MatrixID,VP,ModelMatrixID,cam);
	

		
	//trans
		glm::mat4 vpradio= VP*glm::translate(glm::vec3(-1.5,0.9, -0))*glm::rotate(180.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(0.03f, 0.03f, 0.03f));
		mTexture4->Bind();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &vpradio[0][0]);
		radio->Render(programID, glm::translate(glm::vec3(-1.5, 0.9, -0))*glm::rotate(180.0f, glm::vec3(0, 1, 0))*glm::scale(glm::vec3(0.03f, 0.03f, 0.03f)));
	
		
		
		mTexture3->Bind();
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &myTable->TableModelMatrix[0][0]);
		myTable->Draw(MatrixID, VP, ModelMatrixID, glm::translate(-1.2f, 0.0f, 0.0f));
		
}

void Renderer::Cleanup()
{
    glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
	
	if(m<90&&dooropened==1){
	//m = 0.02;
	
	//doormvp =  glm::rotate((float)squareRotationAngle,glm::vec3(0.0,1.0,0.0))*doormvp ;

	m+=0.2;
	}
	else if(dooropened==0&&m>0){
		
	//doormvp =  glm::rotate((float)squareRotationAngle,glm::vec3(0.0,1.0,0.0))*doormvp ;

		m-=0.2;
	}
	double squareRotationAngle = m*deltaTime;
	//doormvp =  glm::rotate((float)squareRotationAngle,glm::vec3(0.0,1.0,0.0))*doormvp ;
	doormvp = glm::rotate(m, glm::vec3(0.0, 1.0, 0.0))*glm::translate(-0.5f,0.0f,0.0f)*glm::scale(5.0f,2.0f,0.5f);
}

void Renderer::HandleKeyboardInput(int key)
{
	glm::vec3 mPosition=myCamera->GetEyePosition();
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
		myCamera->Walk(0.5);
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		myCamera->Walk(-0.5);
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
		myCamera->Strafe(0.1);
		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		myCamera->Strafe(-0.1);
		break;

		// Moving up
	case GLFW_KEY_SPACE:
	case GLFW_KEY_R:
		myCamera->Fly(0.1);
		break;

		// Moving down
	case GLFW_KEY_LEFT_CONTROL:
	case GLFW_KEY_F:
		myCamera->Fly(-0.1);
		break;
		case GLFW_KEY_Z:
		//	glm::vec3 eyePt= myCamera->GetEyePosition();
			/*myCamera->Reset(0.0,1.0,2.0,
					0,0,0,
					0,1,0);*/
			myCamera->mAngleX=0;
			myCamera->mAngleY=0;
		break;
		case GLFW_KEY_C:
		//	PlaySound(TEXT("skoon.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

				cam = 1;
				glUniform1i(mRenderingModeID, 1);
			
		break;
		case GLFW_KEY_V:
		//	PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
				cam=-1;
				break;
		case GLFW_KEY_O:
			//	PlaySound(TEXT("skoon.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

			glUniform1i(mRenderingModeID, 1);

			break;
		case GLFW_KEY_P:
			//	PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
			if(cam==-1)
			glUniform1i(mRenderingModeID, 2);
			else
				glUniform1i(mRenderingModeID, 0);
			break;
		case GLFW_KEY_U:
				PlaySound(TEXT("MyAppSound"), NULL, SND_APPLICATION);
			
			break;
		case GLFW_KEY_I:
				PlaySound(TEXT("skoon.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

			break;
	default:
		break;
	}
	if(cam==1){
		
	myCamera2->UpdateViewMatrix();
	glUniform3fv(EyePositionID,1, &myCamera2->GetEyePosition()[0]);
	}
	//continue the remaining movements.
	else{
	myCamera->UpdateViewMatrix();
	
	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	Dir = myCamera->GetLookDirection();
	glUniform3fv(DirID, 1, &Dir[0]);
	}
	if(myCamera->GetEyePosition()[2]<=0.25&&myCamera->GetEyePosition()[0]>1.0)
		dooropened=1;
	else
		dooropened=0;

}

void Renderer::HandleMouse(double deltaX,double deltaY)
{	
	myCamera->Yaw(deltaX);
	myCamera->Pitch(deltaY);
	myCamera->UpdateViewMatrix();
	//update the eye position uniform.
	glUniform3fv(EyePositionID,1, &myCamera->GetEyePosition()[0]);
	Dir = myCamera->GetLookDirection();
	glUniform3fv(DirID, 1, &Dir[0]);
}
bool Renderer::lLoadingmenu() {
	Model mSquare = Model();
	mSquare.VertexData.push_back(glm::vec3(-0.5f, 0.95f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(0.5f, 0.95f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(0.5f, 1.0f, 0.0f));
	mSquare.VertexData.push_back(glm::vec3(-0.5f, 1.0f, 0.0f));
	//we want a gray cube cube.
	mSquare.ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	mSquare.ColorData.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	//first.riangle.
	mSquare.IndicesData.push_back(0);
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(3);
	//secon.triangle.
	mSquare.IndicesData.push_back(1);
	mSquare.IndicesData.push_back(2);
	mSquare.IndicesData.push_back(3);
	mSquare.Initialize();
	glm::mat4 VP;
	glm::mat4 VP1;
	VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	VP1 = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	mTexture3->Bind();
	
		VP = VP*glm::translate(0.0f, 1.0f, 0.0f)*glm::rotate(n, glm::vec3(0.0, 0.0, 1.0))*glm::translate(0.0f, -1.0f, 0.0f);
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP[0][0]);
		mSquare.Draw();
		VP1 = VP1*glm::translate(0.0f, 1.0f, 0.0f)*glm::rotate(n, glm::vec3(0.0, 0.0, 1.0))*glm::rotate(90.0f, glm::vec3(0.0, 0.0, 1.0))*glm::translate(0.0f, -1.0f, 0.0f);

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &VP1[0][0]);
		mSquare.Draw();
		n++;
		if (n >= 2000)
			return 0;
		else
			return 1;
}