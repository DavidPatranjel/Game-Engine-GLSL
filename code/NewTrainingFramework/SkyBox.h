#pragma once
#include "SceneObject.h"
class SkyBox :
    public SceneObject
{
public:
    Vector3 followingCamera;
public:
    SkyBox(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
        Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, Vector3 followingcamera);
    void Draw(Camera* activeCamera, ESContext* esContext);
    ~SkyBox();
};

