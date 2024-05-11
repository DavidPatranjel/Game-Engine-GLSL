#include "stdafx.h"
#include "PointLight.h"

PointLight::PointLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, const Vector3& _position)
    : Light(_id, _type, _diffuseColor, _specularColor, _specPower), position(_position) {
    // Constructor body
}