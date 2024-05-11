#pragma once
#include "../Utilities/utilities.h"

class Light
{
public:
	int id, type;
	Vector3 diffuseColor, specularColor;
	float specPower;

public:
	Light(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower);
	virtual ~Light() {};
};

