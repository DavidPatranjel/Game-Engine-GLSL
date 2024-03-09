#pragma once
#include "SceneObject.h"
class Terrain :
    public SceneObject
{
private:
    int N;
    float D;
    Vector3 heights;

public:
    Terrain(int objectId, const std::string& _name, const Vector3& objectColor, const Vector3& objectPosition, const Vector3& objectRotation, const Vector3& objectScale,
        Model* objectModel, Shader* objectShader, const std::vector<Texture*>& objectTexture, bool useDepthTest, 
        int n, float d, Vector3 h);
    void Draw(Camera* activeCamera, ESContext* esContext);
    ~Terrain();
    float getCellDimension();
    void updateXPos(float dist);
    void updateZPos(float dist);
};

