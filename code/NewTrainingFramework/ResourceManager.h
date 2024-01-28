#pragma once
#include <unordered_map>
#include "ModelResource.h"
#include "ShaderResource.h"
#include "TextureResource.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
private:
	char* modelPath;
	char* shaderPath;
	char* texturePath;
	std::unordered_map<int, ModelResource*> modelResources;
	std::unordered_map<int, ShaderResource*> shaderResources;
	std::unordered_map<int, TextureResource*> textureResources;
	std::unordered_map<int, Model*> models;
	std::unordered_map<int, Shader*> shaders;
	std::unordered_map<int, Texture*> textures;

	static ResourceManager* spInstance;
	ResourceManager() {};
public:
	static ResourceManager* getInstance();
	void Init(const char* resourceFileXML);
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor
	~ResourceManager();

	template<typename T>
	T* addOrRetrieveElement(std::unordered_map<int, T*>& resourceMap, int key, T* value)
	{
		auto it = resourceMap.find(key);
		if (it == resourceMap.end())
		{
			// Key not found, add the new element
			resourceMap[key] = value;
		}
		else
		{
			// Key found, return the existing element
			value = it->second;
		}
		return value;
	}

	Model* loadModel(int modelResourceKey);
	Texture* loadTexture(int textureResourceKey);
	Shader* loadShader(int shaderResourceKey);

};

