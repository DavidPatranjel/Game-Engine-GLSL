#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

class Shader
{
public:
	ShaderResource* sr;

	GLuint program, vertexShader, fragmentShader;
	GLint positionAttribute;
	GLint colorAttribute;
	GLint matrixUniform;
	GLint mMVP;
	GLint uvAttribute;
	GLint textureUniform;

public:
	Shader(ShaderResource* shader) 
	{
		sr = shader;
	}
	~Shader();
	int Load(char* folder);
};

