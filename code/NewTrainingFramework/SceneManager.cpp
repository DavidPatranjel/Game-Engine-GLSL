#include "stdafx.h"
#include "SceneManager.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace rapidxml;

SceneManager* SceneManager::spInstance = NULL;

SceneManager* SceneManager::getInstance()
{
    if (!spInstance)
    {
        spInstance = new SceneManager();
    }
    return spInstance;

}


void SceneManager::Init(const char* resourceFileXML)
{
	ResourceManager* resourceManager = ResourceManager::getInstance();

	std::ifstream file(resourceFileXML);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string xmlContent(buffer.str());

	// Create an XML document object
	xml_document<> doc;
	doc.parse<0>(&xmlContent[0]);
	std::cout << "Name of my first node is: " << doc.first_node()->name() << "\n";

	xml_node<>* pRoot = doc.first_node();


	///Read gameName
	char* name = pRoot->first_node("gameName")->value();
	gameName = new char[strlen(name) + 1];
	strcpy_s(gameName, strlen(name) + 1, name);
	
	///Read defaultScreenSize
	screenWidth = std::stoi(pRoot -> first_node("defaultScreenSize") -> first_node("width") -> value());
	screenHeight = std::stoi(pRoot ->first_node("defaultScreenSize")->first_node("height")->value());

	///Read backgroundColor
	backgroundColor.x = atof(pRoot->first_node("backgroundColor")->first_node("r")->value());
	backgroundColor.y = atof(pRoot->first_node("backgroundColor")->first_node("g")->value());
	backgroundColor.z = atof(pRoot->first_node("backgroundColor")->first_node("b")->value());

	///Read controls

	///Read cameras
	xml_node<>* pCameras = pRoot->first_node("cameras");
	for (xml_node<>* pNode = pCameras->first_node("camera"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		char* type = pNode->first_node("type")->value(); ///ce facem aici?
		Vector3 position, target, up;
		position.x = atof(pNode->first_node("position")->first_node("x")->value());
		position.y = atof(pNode->first_node("position")->first_node("y")->value());
		position.z = atof(pNode->first_node("position")->first_node("z")->value());

		target.x = atof(pNode->first_node("target")->first_node("x")->value());
		target.y = atof(pNode->first_node("target")->first_node("y")->value());
		target.z = atof(pNode->first_node("target")->first_node("z")->value());
		
		up.x = atof(pNode->first_node("up")->first_node("x")->value());
		up.y = atof(pNode->first_node("up")->first_node("y")->value());
		up.z = atof(pNode->first_node("up")->first_node("z")->value());

		float transSpeed = atof(pNode->first_node("translationSpeed")->value());
		float rotSpeed = atof(pNode->first_node("rotationSpeed")->value());
		float fov = atof(pNode->first_node("fov")->value());
		float nearVal = atof(pNode->first_node("near")->value());
		float farVal = atof(pNode->first_node("far")->value());

		std::cout << "camera ID: " << id << std::endl;
		std::cout << "camera position: " << position.x << " " <<position.y << " " << position.z << std::endl;
		std::cout << "camera target: " << target.x <<" " <<target.y <<" "<<target.z << std::endl;

		///ce facem cu type
		Camera* cam = new Camera(position, target, up,
			transSpeed, rotSpeed, nearVal, farVal, fov);
		addOrRetrieveElement(cameras, id, cam);

		std::cout << std::endl;
	}

	///Read activecam
	activeCamera = std::stoi(pRoot->first_node("activeCamera")->value());

	///Read objects
	
	xml_node<>* pObjects = pRoot->first_node("objects");
	for (xml_node<>* pNode = pObjects->first_node("object"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		int modelID = std::stoi(pNode->first_node("model")->value());
		int shaderID = std::stoi(pNode->first_node("shader")->value());
		char* type = pNode->first_node("type")->value();
		xml_node<>* pWiered = pNode->first_node("wired");
		bool wiered = true;
		if (pWiered == 0) wiered = false;
		char* name = pNode->first_node("name")->value();
		Vector3 color, position, rotation, scale;
		xml_node<>* pColor = pNode->first_node("color");
		if (pColor) 
		{
			color.x = atof(pColor->first_node("r")->value());
			color.y = atof(pColor->first_node("g")->value());
			color.z = atof(pColor->first_node("b")->value());
		}
		position.x = atof(pNode->first_node("position")->first_node("x")->value());
		position.y = atof(pNode->first_node("position")->first_node("y")->value());
		position.z = atof(pNode->first_node("position")->first_node("z")->value());

		rotation.x = atof(pNode->first_node("rotation")->first_node("x")->value());
		rotation.y = atof(pNode->first_node("rotation")->first_node("y")->value());
		rotation.z = atof(pNode->first_node("rotation")->first_node("z")->value());

		scale.x = atof(pNode->first_node("scale")->first_node("x")->value());
		scale.y = atof(pNode->first_node("scale")->first_node("y")->value());
		scale.z = atof(pNode->first_node("scale")->first_node("z")->value());

		std::cout << "object ID: " << id << std::endl;
		std::cout << "object position: " << position.x << " " << position.y << " " << position.z << std::endl;
		std::cout << "object color: " << color.x << " " << color.y << " " << color.z << std::endl;

		Model* model = resourceManager->loadModel(modelID);
		Shader* shader = resourceManager->loadShader(shaderID);
		std::vector<Texture*> textures;

		xml_node<>* pTextures = pNode->first_node("textures");
		if (pTextures != 0) 
		{
			for (xml_node<>* pNodeTexture = pTextures->first_node("texture"); pNodeTexture; pNodeTexture = pNodeTexture->next_sibling())
			{
				int textureID = std::stoi(pNodeTexture->first_attribute("id")->value());
				Texture* texture = resourceManager->loadTexture(textureID);
				textures.push_back(texture);
			}
		}

		SceneObject* object = new SceneObject(id, color, position, rotation, scale, model, shader, textures, true);
		addOrRetrieveElement(sceneObjects, id, object);

		std::cout << std::endl;
	}
	
	//Read debugsettings
	//Read objectaxes
	Vector3 ox, oy, oz;
	ox.x = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("r")->value());
	ox.y = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("g")->value());
	ox.z = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("b")->value());
	oy.x = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("r")->value());
	oy.y = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("g")->value());
	oy.z = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("b")->value());
	oz.x = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("r")->value());
	oz.y = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("g")->value());
	oz.z = atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("b")->value());
	objectAxes.push_back(ox);
	objectAxes.push_back(oy);
	objectAxes.push_back(oz);

	//Read objectaxes
	ox.x = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("r")->value());
	ox.y = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("g")->value());
	ox.z = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("b")->value());
	oy.x = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("r")->value());
	oy.y = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("g")->value());
	oy.z = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("b")->value());
	oz.x = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("r")->value());
	oz.y = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("g")->value());
	oz.z = atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("b")->value());
	objectAxes.push_back(ox);
	objectAxes.push_back(oy);
	objectAxes.push_back(oz);



}
