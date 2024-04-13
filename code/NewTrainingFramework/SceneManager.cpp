#include "stdafx.h"
#include "SceneManager.h"
#include "Terrain.h"
#include "Skybox.h"
#include "SkyboxReflectionObject.h"
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

void SceneManager::freeResources()
{
	delete[] gameName;
	for (auto& entry : cameras)
		delete entry.second;

	for (auto& entry : sceneObjects)
		delete entry.second;
}


void SceneManager::Update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime > Globals::frameTime)
	{
		// do action
		cameras[activeCamera] -> setDeltaTime(totalTime);
		totalTime = 0.0f;
	}

	if (mainTerrain)
	{
		Vector3 terrainPos = sceneObjects[mainTerrain]->getPosition();
		Vector3 cameraPos = cameras[activeCamera]->position;
		dx = cameraPos.x - terrainPos.x;
		dz = cameraPos.z - terrainPos.z;


		if (abs(dx) > dim)
		{
			int translation = (dx > 0) ? dim : -dim;
			sceneObjects[mainTerrain]->updateXPos(translation);
		}

		if (abs(dz) > dim)
		{
			int translation = (dz > 0) ? dim : -dim;
			sceneObjects[mainTerrain]->updateZPos(translation);
		}
	}

	if (mainSkybox)
	{
		Vector3 skyboxPos = sceneObjects[mainSkybox]->getPosition();
		Vector3 cameraPos = cameras[activeCamera]->position;
		Vector3 skyboxCameraFollow = dynamic_cast<SkyBox*> (sceneObjects[mainSkybox])->followingCamera;

		if (skyboxCameraFollow[0])
			sceneObjects[mainSkybox]->updateXPos(cameraPos.x - skyboxPos.x);
		
		if (skyboxCameraFollow[1])
			sceneObjects[mainSkybox]->updateYPos(cameraPos.y - skyboxPos.y);
		
		if (skyboxCameraFollow[2])
			sceneObjects[mainSkybox]->updateZPos(cameraPos.z - skyboxPos.z);

	}

}

void SceneManager::Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (const auto& pair : sceneObjects) {
		pair.second -> Draw(cameras[activeCamera], esContext);
	}
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface); //avem nevoie de doua buffere pt a randa frumos

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
	backgroundColor.x = (GLfloat)atof(pRoot->first_node("backgroundColor")->first_node("r")->value());
	backgroundColor.y = (GLfloat)atof(pRoot->first_node("backgroundColor")->first_node("g")->value());
	backgroundColor.z = (GLfloat)atof(pRoot->first_node("backgroundColor")->first_node("b")->value());

	///Read controls
	keyboardInput = new KBInput();
	xml_node<>* pControls = pRoot->first_node("controls");
	for (xml_node<>* pNode = pControls ->first_node("control"); pNode; pNode = pNode->next_sibling())
	{
		char* key = pNode->first_node("key")->value();
		char k = *key;
		std::string action = pNode->first_node("action")->value();
		keyboardInput->BindKey(k, action);
	}

	///Read cameras
	xml_node<>* pCameras = pRoot->first_node("cameras");
	for (xml_node<>* pNode = pCameras->first_node("camera"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		/// type is for first person or third person TBC
		char* type = pNode->first_node("type")->value(); 
		Vector3 position, target, up;
		position.x = (GLfloat)(GLfloat)atof(pNode->first_node("position")->first_node("x")->value());
		position.y = (GLfloat)(GLfloat)atof(pNode->first_node("position")->first_node("y")->value());
		position.z = (GLfloat)(GLfloat)atof(pNode->first_node("position")->first_node("z")->value());

		target.x = (GLfloat)atof(pNode->first_node("target")->first_node("x")->value());
		target.y = (GLfloat)atof(pNode->first_node("target")->first_node("y")->value());
		target.z = (GLfloat)atof(pNode->first_node("target")->first_node("z")->value());
		
		up.x = (GLfloat)atof(pNode->first_node("up")->first_node("x")->value());
		up.y = (GLfloat)atof(pNode->first_node("up")->first_node("y")->value());
		up.z = (GLfloat)atof(pNode->first_node("up")->first_node("z")->value());

		float transSpeed = (GLfloat)atof(pNode->first_node("translationSpeed")->value());
		float rotSpeed = (GLfloat)atof(pNode->first_node("rotationSpeed")->value());
		float fov = (GLfloat)atof(pNode->first_node("fov")->value());
		fov = toRadians(fov);
		float nearVal = (GLfloat)atof(pNode->first_node("near")->value());
		float farVal = (GLfloat)atof(pNode->first_node("far")->value());

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
		std::string name = pNode->first_node("name")->value();
		int shaderID = std::stoi(pNode->first_node("shader")->value());
		char* type = pNode->first_node("type")->value();
		
		xml_node<>* pWiered = pNode->first_node("wired");
		bool wiered = true;
		if (pWiered == 0) wiered = false;

		Vector3 color, position, rotation, scale;
		xml_node<>* pColor = pNode->first_node("color");
		if (pColor) 
		{
			color.x = (GLfloat)atof(pColor->first_node("r")->value());
			color.y = (GLfloat)atof(pColor->first_node("g")->value());
			color.z = (GLfloat)atof(pColor->first_node("b")->value());
		}
		position.x = (GLfloat)atof(pNode->first_node("position")->first_node("x")->value());
		position.y = (GLfloat)atof(pNode->first_node("position")->first_node("y")->value());
		position.z = (GLfloat)atof(pNode->first_node("position")->first_node("z")->value());

		rotation.x = (GLfloat)atof(pNode->first_node("rotation")->first_node("x")->value());
		rotation.y = (GLfloat)atof(pNode->first_node("rotation")->first_node("y")->value());
		rotation.z = (GLfloat)atof(pNode->first_node("rotation")->first_node("z")->value());
		rotation.x = toRadians(rotation.x);
		rotation.y = toRadians(rotation.y);
		rotation.z = toRadians(rotation.z);

		scale.x = (GLfloat)atof(pNode->first_node("scale")->first_node("x")->value());
		scale.y = (GLfloat)atof(pNode->first_node("scale")->first_node("y")->value());
		scale.z = (GLfloat)atof(pNode->first_node("scale")->first_node("z")->value());

		std::cout << "object ID: " << id << std::endl;
		std::cout << "object position: " << position.x << " " << position.y << " " << position.z << std::endl;
		std::cout << "object color: " << color.x << " " << color.y << " " << color.z << std::endl;
		std::cout << std::endl;

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


		char* modelType = pNode->first_node("model")->value();
		Model* model;
		SceneObject* object;
		if (!std::strcmp(type, "terrain"))
		{
			model = new Model(nullptr);
			int N = std::stoi(pNode->first_node("N")->value());
			dim = (GLfloat)atof(pNode->first_node("D")->value());
			xml_node<>* pHeights = pNode->first_node("height");
			int r = std::atoi(pHeights->first_node("r")->value());
			int g = std::atoi(pHeights->first_node("g")->value());
			int b = std::atoi(pHeights->first_node("b")->value());
			Vector3 h(r, g, b);
			model->LoadTerrain(cameras[activeCamera]->position, N, dim);
			object = new Terrain(id, name, color, position, rotation, scale, model, shader, textures, wiered, N, dim, h);
			mainTerrain = id;
		}
		else if (!std::strcmp(type, "skybox"))
		{
			int modelID = std::stoi(modelType);
			model = resourceManager->loadModel(modelID);

			Vector3 followingcamera;
			followingcamera.x = 0; followingcamera.y = 0; followingcamera.z = 0;

			xml_node<>* pFollCam = pNode->first_node("followingcamera");
			if (pFollCam != 0)
			{
				xml_node<>* pFCX = pFollCam->first_node("ox");
				if (pFCX != 0) followingcamera.x = 1;
				xml_node<>* pFCY = pFollCam->first_node("oy");
				if (pFCY != 0) followingcamera.y = 1;
				xml_node<>* pFCZ = pFollCam->first_node("oz");
				if (pFCZ != 0) followingcamera.z = 1;
			}

			object = new SkyBox(id, name, color, position, rotation, scale, model, shader, textures, wiered, followingcamera);
			mainSkybox = id;
		}
		else if (!std::strcmp(type, "skybox_reflected"))
		{
			int modelID = std::stoi(modelType);
			model = resourceManager->loadModel(modelID);

			float alphaReflection = 0.0f;
			xml_node<>* pReflection = pNode->first_node("reflection");
			if (pReflection != 0) alphaReflection = (GLfloat)atof(pReflection->value());
			object = new SkyboxReflectionObject(id, name, color, position, rotation, scale, model, shader, textures, wiered, alphaReflection);

		}
		else
		{
			int modelID = std::stoi(modelType);
			model = resourceManager->loadModel(modelID);
			object = new SceneObject(id, name, color, position, rotation, scale, model, shader, textures, wiered);
		}

		addOrRetrieveElement(sceneObjects, id, object);

	}
	
	//Read fog
	xml_node<>* pFog = pRoot->first_node("fog");
	if (pFog != 0)
	{
		Vector3 color;
		color.x = (GLfloat)atof(pFog -> first_node("color")->first_node("r")->value());
		color.y = (GLfloat)atof(pFog->first_node("color")->first_node("g")->value());
		color.z = (GLfloat)atof(pFog->first_node("color")->first_node("b")->value());
		float r = atof(pFog->first_node("r")->value());
		float R = atof(pFog->first_node("R")->value());
		fog = new Fog(color, r, R);
	}

	//Read debugsettings
	//Read objectaxes
	Vector3 ox, oy, oz;
	ox.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("r")->value());
	ox.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("g")->value());
	ox.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OXColor")->first_node("b")->value());
	oy.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("r")->value());
	oy.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("g")->value());
	oy.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OYColor")->first_node("b")->value());
	oz.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("r")->value());
	oz.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("g")->value());
	oz.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("objectAxes")->first_node("OZColor")->first_node("b")->value());
	objectAxes.push_back(ox);
	objectAxes.push_back(oy);
	objectAxes.push_back(oz);

	//Read camaxes
	ox.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("r")->value());
	ox.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("g")->value());
	ox.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OXColor")->first_node("b")->value());
	oy.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("r")->value());
	oy.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("g")->value());
	oy.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OYColor")->first_node("b")->value());
	oz.x = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("r")->value());
	oz.y = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("g")->value());
	oz.z = (GLfloat)atof(pRoot->first_node("debugSettings")->first_node("camAxes")->first_node("OZColor")->first_node("b")->value());
	camAxes.push_back(ox);
	camAxes.push_back(oy);
	camAxes.push_back(oz);
}

Vector3 SceneManager::getCameraPosition()
{
	return cameras[activeCamera] -> position;
}


void SceneManager::moveActiveCameraOX(int sense)
{
	cameras[activeCamera] -> moveOx(sense);
}

void SceneManager::moveActiveCameraOY(int sense)
{
	cameras[activeCamera]->moveOy(sense);
}

void SceneManager::moveActiveCameraOZ(int sense)
{
	cameras[activeCamera]->moveOz(sense);
}

void SceneManager::rotateActiveCameraOX(int sense)
{
	cameras[activeCamera]->rotateOx(sense);
}

void SceneManager::rotateActiveCameraOY(int sense)
{
	cameras[activeCamera]->rotateOy(sense);

}

void SceneManager::rotateActiveCameraOZ(int sense)
{
	cameras[activeCamera]->rotateOz(sense);

}