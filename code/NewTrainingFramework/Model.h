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
private:
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
	~Model() {};
	void Load(char* folder);
	ModelResource* getResource()
	{
		return mr;
	}
private:
	Vertex parseIndexLine(const std::string& line);
	Vertex parseVertexLine(const std::string& line);
	void parseFile(const std::string& filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices, int& numVertices, int& numIndices);
	void writeVerticesAndIndices(const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices);

};

