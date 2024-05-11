#pragma once
#include "Light.h"
class SpotLight :
    public Light
{
public:
    float angle;
    Vector3 position, direction;

public:
    SpotLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, float _angle, const Vector3& _position, const Vector3& _direction);

};

