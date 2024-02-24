#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"
#include <unordered_map>

class Texture
{
public:
	TextureResource* tr;
	GLuint textureID;

	std::unordered_map<std::string, int> textureData = {
		{"LINEAR", GL_LINEAR},
		{"NEAREST", GL_NEAREST},
		{"CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE}
	};
public:
	Texture(TextureResource* texture)
	{
		tr = texture;
	};
	~Texture() 
	{
		glDeleteBuffers(1, &textureID);
	}
	void Load(char* folder);
};

