#pragma once
#include "SceneObject.h"
class Fire :
    public SceneObject
{
public:
    float disp_max;
    float u_time = 0.0f;

    Fire(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
        Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, float _dispmax);
    void Update();
    void Draw(Camera* activeCamera, ESContext* esContext);
    ~Fire();
};

