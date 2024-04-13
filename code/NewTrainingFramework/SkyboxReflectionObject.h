#pragma once
#include "SceneObject.h"
class SkyboxReflectionObject :
    public SceneObject
{
public:
    float alphaReflection;

    SkyboxReflectionObject(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
        Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, float _alphaReflection);
    void Draw(Camera* activeCamera, ESContext* esContext);
    ~SkyboxReflectionObject();
};


