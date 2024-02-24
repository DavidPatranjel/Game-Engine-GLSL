#include "stdafx.h"
#include "SceneObject.h"
#include "Shader.h"

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

	Matrix T; T.SetTranslation(position);
	Matrix Rx; Rx.SetRotationX(rotation.x);
	Matrix Ry; Ry.SetRotationY(rotation.y);
	Matrix Rz; Rz.SetRotationZ(rotation.z);
	Matrix S; S.SetScale(scale);

	modelMatrix = T * Rz * Ry * Rx * S;
	//modelMatrix = T * S;
	
}

void SceneObject::Draw(Camera* activeCamera, ESContext* esContext)
{
	//desenez modelul
	glUseProgram(shader -> program);

	glBindBuffer(GL_ARRAY_BUFFER, model -> verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model -> indicesID);
	glBindTexture(GL_TEXTURE_2D, texture[0]->textureID);

	if (shader -> positionAttribute != -1)
	{
		glEnableVertexAttribArray(shader -> positionAttribute);
		glVertexAttribPointer(shader -> positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (shader -> uvAttribute != -1)
	{
		glEnableVertexAttribArray(shader -> uvAttribute);
		glVertexAttribPointer(shader -> uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5));
	}

	if (shader -> mMVP != -1)
	{
		Matrix mvp = modelMatrix * activeCamera -> viewMatrix * activeCamera -> perspectiveMatrix;
		glUniformMatrix4fv(shader -> mMVP, 1, GL_FALSE, (GLfloat*)mvp.m);
	}

	// desenez textura
	glActiveTexture(GL_TEXTURE0);
	if (shader->textureUniform != -1)
	{
		glUniform1i(shader->textureUniform, 0);
	}

	glDrawElements(GL_TRIANGLES, model -> noIndices, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);



	
}