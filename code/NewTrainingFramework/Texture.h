#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"
#include <unordered_map>

struct offset
{
	int cells, row;
};

class Texture
{
public:
	TextureResource* tr;
	GLuint textureID;
	GLuint textureType;
	std::vector<offset> offsetCubeTexture = {
		offset{4, 2},
		offset{4, 0},
		offset{0, 1},
		offset{8, 1},
		offset{4, 1},
		offset{4, 3}
	};
	std::unordered_map<std::string, int> textureData = {
		{"LINEAR", GL_LINEAR},
		{"NEAREST", GL_NEAREST},
		{"CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE},
		{"GL_REPEAT", GL_REPEAT}
	};
public:
	Texture(TextureResource* texture)
	{
		tr = texture;
		if (!strcmp(tr->type, "2d"))
		{
			textureType = GL_TEXTURE_2D;
		}
		else if (!strcmp(tr->type, "cube"))
		{
			textureType = GL_TEXTURE_CUBE_MAP;
		}
	};
	~Texture() 
	{
		glDeleteBuffers(1, &textureID);
	}
	void Load(char* folder);
};

