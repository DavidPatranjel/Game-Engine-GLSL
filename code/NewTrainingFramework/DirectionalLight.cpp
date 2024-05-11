#include "stdafx.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, const Vector3& _direction)
    : Light(_id, _type, _diffuseColor, _specularColor, _specPower), direction(_direction) {
    // Constructor body
}