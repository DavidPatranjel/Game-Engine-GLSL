#include "stdafx.h"
#include "Fire.h"

#include "stdafx.h"
#include "SkyboxReflectionObject.h"

Fire::Fire(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
	Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, float _dispmax) :
	SceneObject(objectId, _name, objectColor, objectPosition,
		objectRotation, objectScale, objectModel, objectShader, objectTexture, useDepthTest)
{
	disp_max = _dispmax;
}

void Fire::Update()
{
	u_time = clock();
	u_time = (float) u_time/1000;

}

void Fire::Draw(Camera* activeCamera, ESContext* esContext)
{
	glUseProgram(shader->program);

	if (shader->timeUniform != -1)
	{
		glUniform1f(shader->timeUniform, u_time);
	}

	if (shader->dispMaxUniform != -1)
	{
		glUniform1f(shader->dispMaxUniform, disp_max);
	}



	glBindBuffer(GL_ARRAY_BUFFER, model->verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesID);



	generalDraw(activeCamera, esContext);

	glDrawElements(GL_TRIANGLES, model->noIndices, GL_UNSIGNED_SHORT, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Fire::~Fire()
{

}
