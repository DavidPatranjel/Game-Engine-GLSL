#pragma once
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "../Utilities/utilities.h"
#include "ResourceManager.h"

class SceneObject
{

public:
	Matrix modelMatrix;

protected:
	int id;
	Vector3 color, position, rotation, scale;
	Model* model;
	Shader* shader;
	std::vector<Texture*> texture;
	std::string name;
	bool depthTest;

public:
	SceneObject(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
		Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest);
	virtual void Draw(Camera* activeCamera, ESContext* esContext);
	void generalDraw(Camera* activeCamera, ESContext* esContext);
	Vector3 getPosition();
	virtual void updateXPos(float dist);
	virtual void updateYPos(float dist);
	virtual void updateZPos(float dist);
	void updateModelMatrix();
};

