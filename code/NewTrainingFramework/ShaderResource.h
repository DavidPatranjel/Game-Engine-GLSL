#pragma once
class ShaderResource
{
public:
    int idShader;
    char *shaderVS, *shaderFS;

public:
    // Constructor
    ShaderResource(int id, const char* vs, const char* fs)
        : idShader(id), shaderVS(nullptr), shaderFS(nullptr)
    {
        // Allocate memory for shaderVS and shaderFS and copy the strings
        if (vs != nullptr)
        {
            shaderVS = new char[strlen(vs) + 1];
            strcpy_s(shaderVS, strlen(vs) + 1, vs);
        }

        if (fs != nullptr)
        {
            shaderFS = new char[strlen(fs) + 1];
            strcpy_s(shaderFS, strlen(fs) + 1, fs);
        }
    }

    // Destructor
    ~ShaderResource()
    {
        // Release dynamically allocated memory in the destructor
        delete[] shaderVS;
        delete[] shaderFS;
    }
};

