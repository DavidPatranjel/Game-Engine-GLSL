#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

class Shader
{
private:
	ShaderResource* sr;

	GLuint program, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint matrixUniform;
	GLint mMVP;
	GLint uvAttribute;

public:
	Shader(ShaderResource* shader) 
	{
		sr = shader;
	}
	~Shader();
	int Load(char* folder);
};

