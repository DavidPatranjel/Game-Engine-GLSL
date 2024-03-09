#include "stdafx.h"
#include "Terrain.h"

Terrain::Terrain(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
    Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, 
    int n, float d, Vector3 h):
    SceneObject(objectId, _name, objectColor, objectPosition, 
        objectRotation, objectScale, objectModel, objectShader, objectTexture, useDepthTest)
{
    N = n;
    D = d;
	heights = h;
}


void Terrain::Draw(Camera* activeCamera, ESContext* esContext)
{
	glUseProgram(shader->program);

	glBindBuffer(GL_ARRAY_BUFFER, model->verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indicesID);

	if (shader->uv2Attribute != -1)
	{
		glEnableVertexAttribArray(shader->uv2Attribute);
		glVertexAttribPointer(shader->uv2Attribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5 + sizeof(Vector2)));
	}

	if (shader->heightUniform != -1)
	{
		GLfloat data[3] = { heights.x, heights.y, heights.z };
		glUniform3fv(shader->heightUniform, 1, data);
	}

	generalDraw(activeCamera, esContext);
	
	glDrawElements(GL_TRIANGLES, model->noIndices, GL_UNSIGNED_SHORT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Terrain::~Terrain()
{
  
}

float Terrain::getCellDimension()
{
	return D;
}

void Terrain::updateXPos(float dist)
{
	position.x += dist;
	float duv = (float) 1/N;
	if (dist < 0) duv *= -1;
	model -> updateUVX(duv);
	updateModelMatrix();
}

void Terrain::updateZPos(float dist)
{
	position.z += dist;
	float duv = (float) 1/N;
	if (dist < 0) duv *= -1;
	model -> updateUVZ(duv);
	updateModelMatrix();
}