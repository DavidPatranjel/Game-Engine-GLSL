#pragma once
#include "Light.h"
class DirectionalLight :
    public Light
{
public:
    Vector3 direction;

public:
    DirectionalLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, const Vector3& _direction);
};

