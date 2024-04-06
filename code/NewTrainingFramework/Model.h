#pragma once
#include "../Utilities/utilities.h"
#include "ModelResource.h"
#include "Vertex.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class Model
{
public:
	ModelResource* mr;
	GLuint indicesID, wiredID, verticesID;
	int noIndices, noWiredIndices, noVertices;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
public:
	Model(ModelResource* model)
	{
		mr = model;
	}
	~Model() 
	{
		glDeleteBuffers(1, &indicesID);
		glDeleteBuffers(1, &wiredID);
		glDeleteBuffers(1, &verticesID);
	}
	void Load(char* folder);
	void LoadTerrain(Vector3 offset, int N, float D);
	void generateModel(Vector3 offset, int N, float D);
	ModelResource* getResource()
	{
		return mr;
	}

	void updateUVX(float duv);
	void updateUVZ(float duv);
private:
	Vertex parseIndexLine(const std::string& line);
	Vertex parseVertexLine(const std::string& line);
	void parseFile(const std::string& filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices, int& numVertices, int& numIndices);
	void writeVerticesAndIndices(const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices);
	void bindBuffers();
};