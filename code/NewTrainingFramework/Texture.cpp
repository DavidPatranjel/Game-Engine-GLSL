#include "stdafx.h"
#include "Texture.h"
#define MAX_BUFFER 255

void Texture::Load(char* folder)
{
	int TWidth, THeight, TBBP;
	char* texturePath = new char[MAX_BUFFER];
	strcpy_s(texturePath, strlen(folder) + 1, folder);
	strcat_s(texturePath, MAX_BUFFER, tr -> textureTGA);
	char* array_pixels = LoadTGA(texturePath, &TWidth, &THeight, &TBBP);
	delete[] texturePath;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	///poate merg niste verificari in viitor
	///aici nu merge... nu putem folosi char*
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureData[tr -> minFilter]); //ccomportament la redimensionare
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureData[tr -> magFilter]); //ccomportament la redimensionare
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureData[tr -> wrapS]);  // comportamentul la u, v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureData[tr->wrapT]);  // comportamentul la u, v
	if (TBBP == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TWidth, THeight, 0, GL_RGB, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea
	else if (TBBP == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TWidth, THeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea
}