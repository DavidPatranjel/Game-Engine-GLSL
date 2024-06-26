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
	GLint normVecAtribute;
	GLint textureUniform[MAX_TEXTURES];
	GLint heightUniform;
	GLint rFogUniform;
	GLint RFogUniform;
	GLint colorFogUniform;	
	GLint posCameraUniform;
	GLint mMUniform, mVUniform;
	GLint alphaReflectionUniform;
	GLint timeUniform, dispMaxUniform;

	GLint typeUniform;
	GLint lightPosition, lightDirection, angleUniform;
	GLint lightDiffUnifrom, lightSpecUniform, specPowerUniform;
	GLint ambientColorUniform, ratioUniform;

public:
	Shader(ShaderResource* shader) 
	{
		sr = shader;
	}
	~Shader();
	int Load(char* folder);
};

