#pragma once

#include <glm\glm.hpp>
#include <vector>
#include <gl\glew.h>
#include "texture.h"
#include "ShaderProgram.h"
#include "Model\Model.h"

class TexturedModel : public Model
{
	
public:
	TexturedModel();
	~TexturedModel();
	Texture* texture;
	 void Draw();
};


