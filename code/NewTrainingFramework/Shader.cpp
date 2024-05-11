#include "stdafx.h"
#include "Shader.h"
#include <string>
#define MAX_BUFFER 255

int Shader::Load(char* folder)
{
	char* fileVertexShader = new char[255];
	strcpy_s(fileVertexShader, strlen(folder) + 1, folder);
	strcat_s(fileVertexShader, MAX_BUFFER, sr->shaderVS);

	char* fileFragmentShader = new char[255];
	strcpy_s(fileFragmentShader, strlen(folder) + 1, folder);
	strcat_s(fileFragmentShader, MAX_BUFFER, sr->shaderFS);

	vertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (vertexShader == 0)
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);
	delete[] fileVertexShader;
	delete[] fileFragmentShader;

	//finding location of uniforms / attributes
	positionAttribute = glGetAttribLocation(program, "a_posL");
	colorAttribute = glGetAttribLocation(program, "a_color");
	matrixUniform = glGetUniformLocation(program, "u_rotation");
	mMVP = glGetUniformLocation(program, "uMVP");
	uvAttribute = glGetAttribLocation(program, "a_uv");
	uv2Attribute = glGetAttribLocation(program, "a_uv2");
	normVecAtribute = glGetAttribLocation(program, "a_normv");

	for (int i = 0; i < MAX_TEXTURES; i++)
	{ 
		textureUniform[i] = glGetUniformLocation(program, ("u_texture_" + std::to_string(i)).c_str());
	}
	heightUniform = glGetUniformLocation(program, "u_height");
	rFogUniform = glGetUniformLocation(program, "u_r");
	RFogUniform = glGetUniformLocation(program, "u_R");
	colorFogUniform = glGetUniformLocation(program, "u_fog_color");
	posCameraUniform = glGetUniformLocation(program, "u_pos_camera");
	mMUniform = glGetUniformLocation(program, "uM");
	mVUniform = glGetUniformLocation(program, "uV");
	alphaReflectionUniform = glGetUniformLocation(program, "u_alpha_reflection");
	timeUniform = glGetUniformLocation(program, "u_time");
	dispMaxUniform = glGetUniformLocation(program, "u_DispMax");

	typeUniform = glGetUniformLocation(program, "type");
	lightPosition = glGetUniformLocation(program, "u_pos_light");
	lightDirection = glGetUniformLocation(program, "u_direction_light");
	angleUniform = glGetUniformLocation(program, "u_angle");
	lightDiffUnifrom = glGetUniformLocation(program, "c_lightDiff");
	lightSpecUniform = glGetUniformLocation(program, "c_lightSpec");
	specPowerUniform = glGetUniformLocation(program, "SpecPower");
	ambientColorUniform = glGetUniformLocation(program, "c_amb");
	ratioUniform = glGetUniformLocation(program, "ratio");



	return 0;
}

Shader::~Shader()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}