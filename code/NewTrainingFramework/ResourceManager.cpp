#include "stdafx.h"
#include "ResourceManager.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace rapidxml;

ResourceManager* ResourceManager::spInstance = NULL;

ResourceManager* ResourceManager::getInstance()
{
    if (!spInstance)
    {
        spInstance = new ResourceManager();
    }
    return spInstance;

}

void ResourceManager::Init(const char* resourceFileXML)
{
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

	char *path;

	///Read Models from xml
	
	xml_node<>* pModels = pRoot -> first_node("models") -> first_node("folder");
	path = pModels->first_attribute("path")->value();
	if (path != nullptr)
	{
		modelPath = new char[strlen(path) + 1];
		strcpy_s(modelPath, strlen(path) + 1, path);
	}

	for (xml_node<>* pNode = pModels->first_node("model"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		char* file = pNode->first_node("file")->value();
		
		std::cout << "Model ID: " << id << std::endl;
		std::cout << "Model FILE: " << file << std::endl;
		
		ModelResource* modelResource = new ModelResource(id, file);
		addOrRetrieveElement(modelResources, id, modelResource);

		std::cout << std::endl;
		
		
	}
	
	///Read Shaders from xml
	xml_node<>* pShaders = pRoot->first_node("shaders")->first_node("folder");
	path = pShaders->first_attribute("path")->value();
	if (path != nullptr)
	{
		shaderPath = new char[strlen(path) + 1];
		strcpy_s(shaderPath, strlen(path) + 1, path);
	}

	for (xml_node<>* pNode = pShaders->first_node("shader"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		char* vs = pNode->first_node("vs")->value();
		char* fs = pNode->first_node("fs")->value();

		std::cout << "Shader ID: " << id << std::endl;
		std::cout << "Shader VS: " << vs << std::endl;
		std::cout << "Shader FS: " << fs << std::endl;

		ShaderResource* shaderResource = new ShaderResource(id, vs, fs);
		addOrRetrieveElement(shaderResources, id, shaderResource);

		std::cout << std::endl;
	}
	
	///Read Textures from xml
	xml_node<>* pTextures = pRoot->first_node("textures")->first_node("folder");
	path = pTextures->first_attribute("path")->value();
	if (path != nullptr)
	{
		texturePath = new char[strlen(path) + 1];
		strcpy_s(texturePath, strlen(path) + 1, path);
	}

	for (xml_node<>* pNode = pTextures->first_node("texture"); pNode; pNode = pNode->next_sibling())
	{
		int id = std::stoi(pNode->first_attribute("id")->value());
		char* texturetype = pNode->first_attribute("type")->value();
		char* file = pNode->first_node("file")->value();
		char* minf = pNode->first_node("min_filter")->value();
		char* magf = pNode->first_node("mag_filter")->value();
		char* wraps = pNode->first_node("wrap_s")->value();
		char* wrapt = pNode->first_node("wrap_t")->value();

		std::cout << "Texture ID: " << id << std::endl;
		std::cout << "Texture Type: " << texturetype << std::endl;
		std::cout << "Texture File: " << file << std::endl;
		std::cout << "Texture MINF: " << minf << std::endl;
		std::cout << "Texture MAGF: " << magf << std::endl;
		std::cout << "Texture WRAPS: " << wraps << std::endl;
		std::cout << "Texture WRAPT: " << wrapt << std::endl;

		TextureResource* textureResource = new TextureResource(id, texturetype, file, minf, magf, wraps, wrapt);
		addOrRetrieveElement(textureResources, id, textureResource);

		std::cout << std::endl;
	}
	
	
}

void ResourceManager::freeResources()
{
	delete[] modelPath;
	delete[] shaderPath;
	delete[] texturePath;
}

Model* ResourceManager::loadModel(int modelResourceKey)
{
	auto itmr = modelResources.find(modelResourceKey);
	if (itmr == modelResources.end()) return nullptr;

	ModelResource* findModelResource = modelResources[modelResourceKey];


	auto itm = models.find(modelResourceKey);
	if (itm == models.end())
	{
		models[modelResourceKey] = new Model(findModelResource);
		models[modelResourceKey]->Load(modelPath);
	}
	return models[modelResourceKey];

}

Texture* ResourceManager::loadTexture(int textureResourceKey)
{
	auto ittr = textureResources.find(textureResourceKey);
	if (ittr == textureResources.end()) return nullptr;

	TextureResource* findTextureResource = textureResources[textureResourceKey];


	auto itt = textures.find(textureResourceKey);
	if (itt == textures.end())
	{
		textures[textureResourceKey] = new Texture(findTextureResource);
		textures[textureResourceKey]->Load(texturePath);
	}
	return textures[textureResourceKey];
}


Shader* ResourceManager::loadShader(int shaderResourceKey)
{
	auto itsr = shaderResources.find(shaderResourceKey);
	if (itsr == shaderResources.end()) return nullptr;

	ShaderResource* findShaderResource = shaderResources[shaderResourceKey];


	auto its = shaders.find(shaderResourceKey);
	if (its == shaders.end())
	{
		shaders[shaderResourceKey] = new Shader(findShaderResource);
		shaders[shaderResourceKey]->Load(shaderPath);
	}
	return shaders[shaderResourceKey];
}

ResourceManager::~ResourceManager()
{
	// Delete all ModelResources
	for (auto& entry : modelResources)
		delete entry.second;

	// Delete all ShaderResources
	for (auto& entry : shaderResources)
		delete entry.second;

	// Delete all TextureResources
	for (auto& entry : textureResources)
		delete entry.second;

	// Delete all Models
	for (auto& entry : models)
		delete entry.second;

	// Delete all Shaders
	for (auto& entry : shaders)
		delete entry.second;

	// Delete all Textures
	for (auto& entry : textures)
		delete entry.second;

	// Release the memory for char pointers
	delete[] modelPath;
	delete[] shaderPath;
	delete[] texturePath;
}