#include "stdafx.h"
#include "Light.h"

Light::Light(int _id, int _type, const Vector3& _diffuseColor, const Vector3& _specularColor, float _specPower): 
    id(_id), type(_type), diffuseColor(_diffuseColor), specularColor(_specularColor), specPower(_specPower) {
    
}