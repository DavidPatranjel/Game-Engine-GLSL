#include "stdafx.h"
#include "Model.h"
#define MAX_BUFFER 255

void Model::Load(char* folder)
{
	char* filePath = new char[MAX_BUFFER];
	strcpy_s(filePath, strlen(folder) + 1, folder);
	strcat_s(filePath, MAX_BUFFER, mr -> modelNFG);
	std::cout << filePath << std::endl;
	parseFile(filePath, vertices, indices, noVertices, noIndices);
	delete[] filePath;

	//buffer object -> GPU
	glGenBuffers(1, &verticesID); //idul poate fi modif (address)
	glBindBuffer(GL_ARRAY_BUFFER, verticesID);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); //asign memory, where is the data (pointer of first value), 
	glBindBuffer(GL_ARRAY_BUFFER, 0); //closes the buffer, (if the type changed another buffer would open... but 0 is not valid)

	//buffer object -> GPU
	glGenBuffers(1, &indicesID); //idul poate fi modif (address)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW); //asign memory, where is the data (pointer of first value), 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //closes the buffer, (if the type changed another buffer would open... but 0 is not valid)

}

Vertex Model::parseVertexLine(const std::string& line)
{
	Vertex v;
	char dummy;

	// Find the position part
	size_t posStart = line.find("pos:[") + 5;
	size_t posEnd = line.find("];", posStart);
	std::string posStr = line.substr(posStart, posEnd - posStart);

	// Parse position
	std::istringstream posStream(posStr);
	posStream >> v.pos.x >> dummy >> v.pos.y >> dummy >> v.pos.z;

	// Default colors
	v.color.x = 1.0f; v.color.y = 1.0f; v.color.z = 1.0f;

	// Find the normal part
	size_t normStart = line.find("norm:[") + 6;
	size_t normEnd = line.find("];", normStart);
	std::string normStr = line.substr(normStart, normEnd - normStart);

	// Parse normal
	std::istringstream normStream(normStr);
	normStream >> v.norm.x >> dummy >> v.norm.y >> dummy >> v.norm.z;

	// Find the binormal part
	size_t binormStart = line.find("binorm:[") + 8;
	size_t binormEnd = line.find("];", binormStart);
	std::string binormStr = line.substr(binormStart, binormEnd - binormStart);

	// Parse binormal
	std::istringstream binormStream(binormStr);
	binormStream >> v.binorm.x >> dummy >> v.binorm.y >> dummy >> v.binorm.z;

	// Find the tangent part
	size_t tgtStart = line.find("tgt:[") + 5;
	size_t tgtEnd = line.find("];", tgtStart);
	std::string tgtStr = line.substr(tgtStart, tgtEnd - tgtStart);

	// Parse tangent
	std::istringstream tgtStream(tgtStr);
	tgtStream >> v.tgt.x >> dummy >> v.tgt.y >> dummy >> v.tgt.z;

	// Find the UV part
	size_t uvStart = line.find("uv:[") + 4;
	size_t uvEnd = line.find("];", uvStart);
	std::string uvStr = line.substr(uvStart, uvEnd - uvStart);

	// Parse UV
	std::istringstream uvStream(uvStr);
	uvStream >> v.uv.x >> dummy >> v.uv.y;

	return v;
}

Vertex Model::parseIndexLine(const std::string& line)
{
	Vertex v;
	char dummy;

	// Find the position part
	size_t posStart = line.find("pos:[") + 5;
	size_t posEnd = line.find("];", posStart);
	std::string posStr = line.substr(posStart, posEnd - posStart);

	// Parse position
	std::istringstream posStream(posStr);
	posStream >> v.pos.x >> dummy >> v.pos.y >> dummy >> v.pos.z;

	// Default colors
	v.color.x = 1.0f; v.color.y = 1.0f; v.color.z = 1.0f;

	// Find the normal part
	size_t normStart = line.find("norm:[") + 6;
	size_t normEnd = line.find("];", normStart);
	std::string normStr = line.substr(normStart, normEnd - normStart);

	// Parse normal
	std::istringstream normStream(normStr);
	normStream >> v.norm.x >> dummy >> v.norm.y >> dummy >> v.norm.z;

	// Find the binormal part
	size_t binormStart = line.find("binorm:[") + 8;
	size_t binormEnd = line.find("];", binormStart);
	std::string binormStr = line.substr(binormStart, binormEnd - binormStart);

	// Parse binormal
	std::istringstream binormStream(binormStr);
	binormStream >> v.binorm.x >> dummy >> v.binorm.y >> dummy >> v.binorm.z;

	// Find the tangent part
	size_t tgtStart = line.find("tgt:[") + 5;
	size_t tgtEnd = line.find("];", tgtStart);
	std::string tgtStr = line.substr(tgtStart, tgtEnd - tgtStart);

	// Parse tangent
	std::istringstream tgtStream(tgtStr);
	tgtStream >> v.tgt.x >> dummy >> v.tgt.y >> dummy >> v.tgt.z;

	// Find the UV part
	size_t uvStart = line.find("uv:[") + 4;
	size_t uvEnd = line.find("];", uvStart);
	std::string uvStr = line.substr(uvStart, uvEnd - uvStart);

	// Parse UV
	std::istringstream uvStream(uvStr);
	uvStream >> v.uv.x >> dummy >> v.uv.y;

	return v;
}

void Model::parseFile(const std::string& filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices, int& numVertices, int& numIndices) {
	std::ifstream file(filename);
	std::string word, line;

	while (file >> word)
	{
		if (word == "NrVertices:")
		{
			file >> numVertices;
			std::getline(file, line);

			vertices.resize(numVertices);

			for (int i = 0; i < numVertices; ++i)
			{
				std::getline(file, line);
				//std::cout << line;
				vertices[i] = parseVertexLine(line);
			}
		}

		else if (word == "NrIndices:")
		{
			file >> numIndices;
			std::getline(file, line);

			indices.resize(numIndices);

			for (int i = 0; i < numIndices / 3; ++i) {
				int v0, v1, v2;
				char dummy;

				std::getline(file, line);
				//std::cout << line;

				// Find the indices part
				size_t indicesStart = line.find(".") + 1;
				size_t indicesEnd = line.length();
				std::string indicesStr = line.substr(indicesStart, indicesEnd - indicesStart);

				// Parse indices
				std::istringstream indicesStream(indicesStr);
				indicesStream >> v0 >> dummy >> v1 >> dummy >> v2;

				indices[i * 3] = static_cast<short>(v0);
				indices[i * 3 + 1] = static_cast<short>(v1);
				indices[i * 3 + 2] = static_cast<short>(v2);

			}
		}
	}
}


void Model::writeVerticesAndIndices(const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices) {
	std::cout << "Vertices:" << std::endl;
	for (const auto& vertex : vertices) {
		std::cout << "pos: [" << vertex.pos.x << ", " << vertex.pos.y << ", " << vertex.pos.z << "]; "
			<< "norm: [" << vertex.norm.x << ", " << vertex.norm.y << ", " << vertex.norm.z << "]; "
			<< "binorm: [" << vertex.binorm.x << ", " << vertex.binorm.y << ", " << vertex.binorm.z << "]; "
			<< "tgt: [" << vertex.tgt.x << ", " << vertex.tgt.y << ", " << vertex.tgt.z << "]; "
			<< "uv: [" << vertex.uv.x << ", " << vertex.uv.y << "]; "
			<< "color: [" << vertex.color.x << ", " << vertex.color.y << ", " << vertex.color.z << "]" << std::endl;
	}

	std::cout << "Indices:" << std::endl;
	for (size_t i = 0; i < indices.size() / 3; i += 3) {
		std::cout << indices[i] << ", " << indices[i + 1] << ", " << indices[i + 2] << std::endl;
	}
}