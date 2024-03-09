#pragma once
#include "ShaderResource.h"
#include "../Utilities/utilities.h"

const int MAX_TEXTURES = 5;

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
	GLint uv2Attribute;
	GLint textureUniform[MAX_TEXTURES];
	GLint heightUniform;

public:
	Shader(ShaderResource* shader) 
	{
		sr = shader;
	}
	~Shader();
	int Load(char* folder);
};

