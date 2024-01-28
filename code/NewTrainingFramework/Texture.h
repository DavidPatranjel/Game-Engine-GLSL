#pragma once
#include "TextureResource.h"
#include "../Utilities/utilities.h"
#include <unordered_map>

class Texture
{
private:
	TextureResource* tr;
	GLuint textureID;

	std::unordered_map<char*, int> textureData = {
		{"LINEAR", GL_LINEAR},
		{"NEAREST", GL_NEAREST},
		{"CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE}
	};
public:
	Texture(TextureResource* texture)
	{
		tr = texture;
	};
	~Texture() {};
	void Load(char* folder);
};

