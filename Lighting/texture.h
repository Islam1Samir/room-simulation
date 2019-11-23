#pragma once


#include <string>
#include <GL/glew.h>
class Texture
{
public:
	int width, height;
	int numComponents;
	unsigned char * data;
	int texUnit;
	void Bind();
	Texture(const std::string& fileName, int texUnit);
	virtual ~Texture();
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}
	GLuint m_texture;
};

