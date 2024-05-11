#include "stdafx.h"
#include "SceneObject.h"
#include "Shader.h"
#include "SceneManager.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"

SceneObject::SceneObject(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
	Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest)
{
	id = objectId;
	name = _name;
	color = Vector3(objectColor);
	position = Vector3(objectPosition);
	rotation = Vector3(objectRotation);
	scale = Vector3(objectScale);
	model = objectModel;
	shader = objectShader;
	texture = objectTexture;
	depthTest = useDepthTest;
	
	updateModelMatrix();
	
}

void SceneObject::generalDraw(Camera* activeCamera, ESContext* esContext)
{
	if (shader->positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader->positionAttribute);
		glVertexAttribPointer(shader->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader->uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader->uvAttribute);
		glVertexAttribPointer(shader->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5));
	}

	if (shader->normVecAtribute != -1)
	{
		glEnableVertexAttribArray(shader->normVecAtribute);
		glVertexAttribPointer(shader->normVecAtribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 2));
	}

	if (shader->mMVP != -1)
	{
		Matrix mvp = modelMatrix * activeCamera->viewMatrix * activeCamera->perspectiveMatrix;
		glUniformMatrix4fv(shader->mMVP, 1, GL_FALSE, (GLfloat*)mvp.m);
	}

	if (shader->rFogUniform != -1)
	{
		glUniform1f(shader->rFogUniform, SceneManager::getInstance()->fog->r);
	}

	if (shader->RFogUniform != -1)
	{
		glUniform1f(shader->RFogUniform, SceneManager::getInstance()->fog->R);
	}

	if (shader->colorFogUniform != -1)
	{
		glUniform3f(shader->colorFogUniform, SceneManager::getInstance()->fog->color.x, SceneManager::getInstance()->fog->color.y, SceneManager::getInstance()->fog->color.z);
	}

	if (shader->posCameraUniform != -1)
	{
		Vector3 campos = activeCamera->position;
		glUniform3f(shader->posCameraUniform, campos.x, campos.y, campos.z);
	}

	for (int i = 0; i < texture.size(); i++)
	{		
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(texture[i] ->textureType, texture[i]->textureID);
		if (shader->textureUniform[i] != -1)
		{
			glUniform1i(shader->textureUniform[i], i);
		}
	}

	if (shader->mMUniform != -1)
	{
		glUniformMatrix4fv(shader->mMUniform, 1, GL_FALSE, (GLfloat*)modelMatrix.m);
	}

	if (shader->mVUniform != -1)
	{
		glUniformMatrix4fv(shader->mVUniform, 1, GL_FALSE, (GLfloat*)activeCamera->viewMatrix.m);
	}

	if (shader->typeUniform != -1)
	{
		glUniform1i(shader->typeUniform, SceneManager::getInstance()->lights[0]->type);
	}

	if (shader->lightPosition != -1)
	{
		Light* lightPtr = SceneManager::getInstance()->lights[0];
		PointLight* pointLightPtr = dynamic_cast<PointLight*>(lightPtr);
		if (pointLightPtr) {
			glUniform3f(shader->lightPosition,
				pointLightPtr->position.x,
				pointLightPtr->position.y,
				pointLightPtr->position.z);
		}
		else {
			SpotLight* spotLightPtr = dynamic_cast<SpotLight*>(lightPtr);
			if (spotLightPtr) {
				glUniform3f(shader->lightPosition,
					spotLightPtr->position.x,
					spotLightPtr->position.y,
					spotLightPtr->position.z);
			}

		}
	}

	if (shader->lightDirection != -1)
	{
		Light* lightPtr = SceneManager::getInstance()->lights[0];
		DirectionalLight* dirLightPtr = dynamic_cast<DirectionalLight*>(lightPtr);

		if (dirLightPtr) {
			glUniform3f(shader->lightDirection,
				dirLightPtr->direction.x,
				dirLightPtr->direction.y,
				dirLightPtr->direction.z);
		}
		else {
			SpotLight* spotLightPtr = dynamic_cast<SpotLight*>(lightPtr);
			if (spotLightPtr) {
				glUniform3f(shader->lightDirection,
					spotLightPtr->direction.x,
					spotLightPtr->direction.y,
					spotLightPtr->direction.z);
			}

		}
	}

	if (shader->angleUniform != -1)
	{
		Light* lightPtr = SceneManager::getInstance()->lights[0];
		SpotLight* spotLightPtr = dynamic_cast<SpotLight*>(lightPtr);

		if (spotLightPtr) {
			glUniform1f(shader->angleUniform,
				spotLightPtr->angle);
		}
	}

	if (shader->lightDiffUnifrom != -1)
	{
		glUniform3f(shader->lightDiffUnifrom, 
			SceneManager::getInstance()->lights[0]->diffuseColor.x, 
			SceneManager::getInstance()->lights[0]->diffuseColor.y, 
			SceneManager::getInstance()->lights[0]->diffuseColor.z);
	}

	if (shader->lightSpecUniform != -1)
	{
		glUniform3f(shader->lightSpecUniform, 
			SceneManager::getInstance()->lights[0]->specularColor.x,
			SceneManager::getInstance()->lights[0]->specularColor.y,
			SceneManager::getInstance()->lights[0]->specularColor.z);
	}

	if (shader->specPowerUniform != -1)
	{
		glUniform1f(shader->specPowerUniform, SceneManager::getInstance()->lights[0]->specPower);
	}

	if (shader->ambientColorUniform != -1)
	{
		glUniform3f(shader->ambientColorUniform, 
			SceneManager::getInstance()->ambientLight.ambientColor.x,
			SceneManager::getInstance()->ambientLight.ambientColor.y,
			SceneManager::getInstance()->ambientLight.ambientColor.z);
	}

	if (shader->ratioUniform != -1)
	{
		glUniform1f(shader->ratioUniform, SceneManager::getInstance()->ambientLight.ratio);
	}



}

void SceneObject::Update()
{

}


void SceneObject::Draw(Camera* activeCamera, ESContext* esContext)
{
	//desenez modelul
	glUseProgram(shader -> program);

	glBindBuffer(GL_ARRAY_BUFFER, model -> verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model -> indicesID);

	generalDraw(activeCamera, esContext);

	glDrawElements(GL_TRIANGLES, model->noIndices, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

Vector3 SceneObject::getPosition()
{
	return position;
}

void SceneObject::updateXPos(float dist)
{
	position.x += dist;
	updateModelMatrix();
}

void SceneObject::updateYPos(float dist)
{
	position.y += dist;
	updateModelMatrix();
}

void SceneObject::updateZPos(float dist)
{
	position.z += dist;
	updateModelMatrix();
}

void SceneObject::updateModelMatrix()
{
	Matrix T; T.SetTranslation(position);
	Matrix Rx; Rx.SetRotationX(rotation.x);
	Matrix Ry; Ry.SetRotationY(rotation.y);
	Matrix Rz; Rz.SetRotationZ(rotation.z);
	Matrix S; S.SetScale(scale);

	modelMatrix = S * Rx * Ry * Rz * T;
}