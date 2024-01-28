#pragma once
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"

class SceneObject
{
private:
	int id;
	Vector3 color, position, rotation, scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> texture;
	bool depthTest;
public:
	SceneObject(int objectId, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
		Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest)
		: id(objectId), color(objectColor), position(objectPosition), rotation(objectRotation), scale(objectScale),
		model(objectModel), shader(objectShader), texture(objectTexture), depthTest(useDepthTest)
	{}

};

