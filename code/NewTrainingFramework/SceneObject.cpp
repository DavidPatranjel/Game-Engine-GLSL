#include "stdafx.h"
#include "SceneObject.h"
#include "Shader.h"
#include "SceneManager.h"

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