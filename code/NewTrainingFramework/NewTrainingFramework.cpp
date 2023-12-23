// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../Utilities/TGA.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Globals.h"
#define PI 3.141592
using namespace rapidxml;

float angle = 0.0f, step = 0.1f, totalTime = 0.0f;

GLuint vboId, vboIdLine, verticesID, indicesID, textureID;
Shaders myShaders, myShadersLine, myShadersGeneralObject;
Camera camera;
Matrix mRot;

std::vector<Vertex> vertices;
std::vector<unsigned short> indices;
int noVertices, noIndices;

int TWidth, THeight, TBBP;

//nft file parser code
Vertex parseVertexLine(const std::string& line)
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

Vertex parseIndexLine(const std::string& line)
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

void parseFile(const std::string& filename, std::vector<Vertex>& vertices, std::vector<unsigned short>& indices, int& numVertices, int& numIndices) {
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
				int index, v0, v1, v2;
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

void writeVerticesAndIndices(const std::vector<Vertex>& vertices, const std::vector<unsigned short>& indices) {
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

void parseXML(const char* filePath)
{
	std::ifstream file(filePath);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string xmlContent(buffer.str());

	// Create an XML document object
	xml_document<> doc;
	doc.parse<0>(&xmlContent[0]);
	std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	xml_node<>* pRoot = doc.first_node();

	for (xml_node<>* pNode = pRoot->first_node("obiect"); pNode; pNode = pNode->next_sibling())
	{
		std::cout << "Object ID: " << pNode->first_attribute("id")->value() << std::endl;
		std::cout << "Object Name: " << pNode->first_attribute("nume")->value() << std::endl;

		xml_node<>* modelNode = pNode->first_node("model");
		std::cout << "Model Info: " << modelNode->first_attribute("info")->value() << std::endl;
		std::cout << "Model Value: " << modelNode->value() << std::endl;

		xml_node<>* texturaNode = pNode->first_node("textura");
		std::cout << "Textura Folder: " << texturaNode->first_attribute("folder")->value() << std::endl;
		std::cout << "Textura Value: " << texturaNode->value() << std::endl;

		std::cout << std::endl;
	}
}


int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);
	///parser tests
	std::string filePath = "../../textures/Models/Bus.nfg";
	parseFile(filePath, vertices, indices, noVertices, noIndices);
	//writeVerticesAndIndices(vertices, indices);
	std::cout << vertices.size() << " " << indices.size() << std::endl;

	///load texture
	const char* texturePath = "../../textures/Textures/Bus.tga";
	char* array_pixels =  LoadTGA(texturePath, &TWidth, &THeight, &TBBP);

	///read XML
	const char* XMLPath = "../../textures/exemplu_xml.xml";
	parseXML(XMLPath);

	//triangle data (heap)
	Vertex verticesData[6];

	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.0f;  verticesData[0].pos.z =  0.0f;
	verticesData[0].color.x = 1.0f; verticesData[0].color.y = 0.0f; verticesData[0].color.z = 0.0f;
	verticesData[1].pos.x = 0.5f;  verticesData[1].pos.y = 0.0f;  verticesData[1].pos.z =  0.0f;
	verticesData[1].color.x = 0.0f; verticesData[1].color.y = 1.0f; verticesData[1].color.z = 0.0f;
	verticesData[2].pos.x =  0.0f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	verticesData[2].color.x = 0.0f; verticesData[2].color.y = 0.0f; verticesData[2].color.z = 1.0f;
	verticesData[3].pos.x = 0.5f;  verticesData[3].pos.y = -0.5f;  verticesData[3].pos.z = 0.0f;
	verticesData[3].color.x = 1.0f; verticesData[3].color.y = 1.0f; verticesData[3].color.z = 0.0f;
	verticesData[4].pos.x = 0.5f;  verticesData[4].pos.y = 0.0f;  verticesData[4].pos.z = 0.0f;
	verticesData[4].color.x = 0.0f; verticesData[4].color.y = 1.0f; verticesData[4].color.z = 0.0f;
	verticesData[5].pos.x = 0.0f;  verticesData[5].pos.y = -0.5f;  verticesData[5].pos.z = 0.0f;
	verticesData[5].color.x = 0.0f; verticesData[5].color.y = 0.0f; verticesData[5].color.z = 1.0f;

	Vertex verticesLineData[2];

	verticesLineData[0].pos.x = 0.0f;  verticesLineData[0].pos.y = 1.0f;  verticesLineData[0].pos.z = 0.0f;
	verticesLineData[1].pos.x = 0.0f;  verticesLineData[1].pos.y = -1.0f;  verticesLineData[1].pos.z = 0.0f;

	mRot.SetIdentity();

	//buffer object -> GPU
	glGenBuffers(1, &vboId); //idul poate fi modif (address)
	glBindBuffer(GL_ARRAY_BUFFER, vboId); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); //asign memory, where is the data (pointer of first value), 
	glBindBuffer(GL_ARRAY_BUFFER, 0); //closes the buffer, (if the type changed another buffer would open... but 0 is not valid)

	//buffer object -> GPU
	glGenBuffers(1, &vboIdLine); //idul poate fi modif (address)
	glBindBuffer(GL_ARRAY_BUFFER, vboIdLine);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLineData), verticesLineData, GL_STATIC_DRAW); //asign memory, where is the data (pointer of first value), 
	glBindBuffer(GL_ARRAY_BUFFER, 0); //closes the buffer, (if the type changed another buffer would open... but 0 is not valid)

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

	//texture object -> GPU
	glGenTextures(1, &textureID); // glGenTextures(nr_texturi, locatie_in_care_sa_fie_stocat_id-ul/id-urile)
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //ccomportament la redimensionare
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // comportamentul la u, v
	if(TBBP == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TWidth, THeight, 0, GL_RGB, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea
	else if(TBBP == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TWidth, THeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, array_pixels); // cream imaginea



	//creation of shaders and program
	myShadersGeneralObject.Init("GeneralObjectShaderVS.vs", "GeneralObjectShaderFS.fs");
	myShadersLine.Init("LineShaderVS.vs", "LineShaderFS.fs");
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw ( ESContext *esContext )
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)sizeof(Vector3));
	}

	if (myShaders.mMVP != -1)
	{
		Matrix mvp = camera.viewMatrix * camera.perspectiveMatrix;
		glUniformMatrix4fv(myShaders.mMVP, 1, GL_FALSE, (GLfloat*)mvp.m);
	}

	
	//Shape  rotation
	
	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat*)mRot.m);
	}
	

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//desenez linia

	glUseProgram(myShadersLine.program);

	glBindBuffer(GL_ARRAY_BUFFER, vboIdLine);

	if (myShadersLine.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShadersLine.positionAttribute);
		glVertexAttribPointer(myShadersLine.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	
	glDrawArrays(GL_LINES, 0, 2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//desenez modelul

	glUseProgram(myShadersGeneralObject.program);

	glBindBuffer(GL_ARRAY_BUFFER, verticesID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);

	if (myShadersGeneralObject.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShadersGeneralObject.positionAttribute);
		glVertexAttribPointer(myShadersGeneralObject.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShadersGeneralObject.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShadersGeneralObject.uvAttribute);
		glVertexAttribPointer(myShadersGeneralObject.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector3) * 5));
	}

	if (myShadersGeneralObject.mMVP != -1)
	{
		Matrix mvp = camera.viewMatrix * camera.perspectiveMatrix;
		glUniformMatrix4fv(myShadersGeneralObject.mMVP, 1, GL_FALSE, (GLfloat*)mvp.m);
	}

	glDrawElements(GL_TRIANGLES, noIndices, GL_UNSIGNED_SHORT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	// desenez textura

	glActiveTexture(GL_TEXTURE0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface ); //avem nevoie de doua buffere pt a randa frumos
}

void Update ( ESContext *esContext, float deltaTime )
{
	totalTime += deltaTime;
	if (totalTime > Globals::frameTime)
	{
		// do action
		camera.setDeltaTime(totalTime);
		totalTime = 0.0f;
	}
	
}

void MouseEvent(ESContext* esContext, MouseButtons btn, MouseEvents event, int x, int y)
{
	printf("Mouse position %d %d \n", x, y);
	switch (btn)
	{
	case LEFT_CLICK:
		printf("LEFT CLICK ");
		switch (event)
		{
		case MOUSE_CLICK:
			printf("MOUSE CLICK \n");
			break;
		case MOUSE_DOUBLE_CLICK:
			printf("MOUSE DOUBLE CLICK \n");
			break;
		case MOUSE_DOWN:
		{
			printf("MOUSE DOUWN \n");
			if (x < (float)Globals::screenWidth / 2)
			{
				//caz stanga
				printf("SCREEN LEFT \n");
				angle -= step;
			}
			else
			{
				//caz dreapta
				printf("SCREEN RIGHT\n");
				angle += step;
			}

			if (angle >= 2 * PI)
			{
				angle -= 2 * PI;
			}
			mRot.SetRotationZ(angle);
		}
			break;
		case MOUSE_UP:
			printf("MOUSE UP \n");
			break;
		default:
			break;
		}
		break;

	case RIGHT_CLICK:
		printf("RIGHT CLICK ");
		switch (event)
		{
		case MOUSE_CLICK:
			printf("MOUSE CLICK \n");
			break;
		case MOUSE_DOUBLE_CLICK:
			printf("MOUSE DOUBLE CLICK \n");
			break;
		case MOUSE_DOWN:
			printf("MOUSE DOUWN \n");
			break;
		case MOUSE_UP:
			printf("MOUSE UP \n");
			break;
		default:
			break;
		}

	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	switch (key)
	{
	case 'q':
	case 'Q':
		printf("Q ");
		camera.moveOy(1);
		break;

	case 'w':
	case 'W':
		printf("W ");
		camera.moveOz(-1);
		break;

	case 'a':
	case 'A':
		printf("A ");
		camera.moveOx(-1);
		break;

	case 's':
	case 'S':
		printf("S ");
		camera.moveOz(1);
		break;

	case 'd':
	case 'D':
		printf("D ");
		camera.moveOx(1);
		break;

	case 'e':
	case 'E':
		printf("E ");
		camera.moveOy(-1);
		break;

	case 'o':
	case 'O':
		printf("O ");
		camera.rotateOz(1);		
		break;
	case 'p':
	case 'P':
		printf("P ");
		camera.rotateOz(-1);
		break;
	case VK_UP:
		printf("UP ");
		camera.rotateOx(1);
		break;
	case VK_DOWN:
		printf("DOWN ");
		camera.rotateOx(-1);
		break;
	case VK_LEFT:
		printf("LEFT ");
		camera.rotateOy(1);
		break;
	case VK_RIGHT:
		printf("RIGHT ");
		camera.rotateOy(-1);
		break;
	default:
		break;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext; //main class for graphics

    esInitContext ( &esContext ); //init OPENGL ES (make calls after this f)

	esCreateWindow ( &esContext, "Hello Square", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc (&esContext, MouseEvent);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

