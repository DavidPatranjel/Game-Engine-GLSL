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
	std::string name;
	bool depthTest;
	Matrix modelMatrix;

public:
	SceneObject(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
		Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest);
	void Draw(Camera* activeCamera, ESContext* esContext);

};

