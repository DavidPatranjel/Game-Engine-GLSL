#include "stdafx.h"
#include "SpotLight.h"

SpotLight::SpotLight(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower, float _angle, const Vector3& _position, const Vector3& _direction)
    : Light(_id, _type, _diffuseColor, _specularColor, _specPower), angle(_angle), position(_position), direction(_direction) {
    // Constructor body
}