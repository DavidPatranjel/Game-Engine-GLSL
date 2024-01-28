#include "stdafx.h"
#include "Shader.h"
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

	return 0;
}

Shader::~Shader()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}