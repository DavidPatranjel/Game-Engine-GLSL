#pragma once
#include <vector>
#include "SceneObject.h"
#include "KBInput.h"
#include "../Utilities/utilities.h"

class SceneManager
{
private:
	static SceneManager* spInstance;
	SceneManager() {};
	float totalTime = 0.0f;

	char* gameName;
	int screenWidth, screenHeight;
	Vector3 backgroundColor;
	//controls?

	std::unordered_map<int, Camera*> cameras;
	int activeCamera;
	std::unordered_map<int, SceneObject*> sceneObjects;
	std::vector<Vector3> objectAxes, camAxes;

public:
	KBInput* keyboardInput;
	//std::vector<Lights*> lights; 
public:
	static SceneManager* getInstance();
	void freeResources();//eliberarea zonelor de memorie alocate dinamic - se poate realiza si in destructor
	~SceneManager();

	void Init(const char* resourceFileXML);
	void Draw(ESContext* esContext);
	void Update(float deltaTime);

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

	KBInput* GetKeyboardInput()
	{
		return keyboardInput;
	}

	void moveActiveCameraOX(int sense);
	void moveActiveCameraOY(int sense);
	void moveActiveCameraOZ(int sense);

	void rotateActiveCameraOX(int sense);
	void rotateActiveCameraOY(int sense);
	void rotateActiveCameraOZ(int sense);

private:
	float toRadians(float n) {
		return n * 3.1415 / 180;
	}
};

