#include "stdafx.h"
#include <iostream>
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
	glBindTexture(textureType, textureID);
	///poate merg niste verificari in viitor
	///aici nu merge... nu putem folosi char*
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, textureData[tr -> minFilter]); //ccomportament la redimensionare
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, textureData[tr -> magFilter]); //ccomportament la redimensionare
	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, textureData[tr -> wrapS]);  // comportamentul la u, v
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, textureData[tr->wrapT]);  // comportamentul la u, v
	if (textureType == GL_TEXTURE_2D)
	{
		if (TBBP == 24)
			glTexImage2D(textureType, 0, GL_RGB, TWidth, THeight, 0, GL_RGB, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea
		else if (TBBP == 32)
			glTexImage2D(textureType, 0, GL_RGBA, TWidth, THeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea
	}
	else if (textureType == GL_TEXTURE_CUBE_MAP) 
	{
		int bits = (TBBP / 8);
		int cellWidth = bits * (TWidth / 4),
			cellHeight =  THeight / 3;
		int err;
		err = glGetError();
		std::cout << "Error="<< err << std::endl;
		char* subbufferPixels = new char[cellWidth * cellHeight + 1];

		for (int i = 0; i < 6; ++i)
		{
			int valOffset = offsetCubeTexture[i].cells * cellWidth * cellHeight + 
				offsetCubeTexture[i].row * cellWidth;
			for (int j = 0; j < cellHeight; ++j)
			{
				int cellsSkipped = j * cellWidth * 4 + valOffset;
				strncpy(subbufferPixels + j * cellWidth, array_pixels + cellsSkipped, cellWidth);
			}
			subbufferPixels[cellWidth * cellHeight] = '\0';



			if (TBBP == 24)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, cellWidth / bits, cellHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, subbufferPixels); // cream imaginea
			else if (TBBP == 32)
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, cellWidth / bits, cellHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, subbufferPixels); // cream imaginea
			err = glGetError();

			
		}
		delete[] subbufferPixels;

		

	}

	delete[] array_pixels;

}
