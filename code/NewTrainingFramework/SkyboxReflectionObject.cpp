#include "stdafx.h"
#include "SkyboxReflectionObject.h"

SkyboxReflectionObject::SkyboxReflectionObject(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
	Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, float _alphaReflection) :
	SceneObject(objectId, _name, objectColor, objectPosition,
		objectRotation, objectScale, objectModel, objectShader, objectTexture, useDepthTest)
{
	alphaReflection = _alphaReflection;
}

void SkyboxReflectionObject::Draw(Camera* activeCamera, ESContext* esContext)
{
	glUseProgram(shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, model->verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesID);

	if (shader->alphaReflectionUniform != -1)
	{
		glUniform1f(shader->alphaReflectionUniform, alphaReflection);
	}

	generalDraw(activeCamera, esContext);

	glDrawElements(GL_TRIANGLES, model->noIndices, GL_UNSIGNED_SHORT, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

SkyboxReflectionObject::~SkyboxReflectionObject()
{

}
