#pragma once
#include "Light.h"

class PointLight :
    public Light
{
public:
    Vector3 position;

public:
    PointLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, const Vector3& _position);
};

