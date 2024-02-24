#pragma once
#include <string>
class TextureResource
{
public:
	int idTexture;
	char *type;
    char* textureTGA;
    std::string minFilter, magFilter, wrapS, wrapT;

public:
    // Constructor
    TextureResource(int id, const char* t, const char *texture, 
        const std::string& minf, const std::string& magf, const std::string& wraps, const std::string& wrapt)
        : idTexture (id), type(nullptr), textureTGA(nullptr), minFilter(minf), magFilter(magf), wrapS(wraps), wrapT(wrapt)
    {
        if (t != nullptr)
        {
            type = new char[strlen(t) + 1];
            strcpy_s(type, strlen(t) + 1, t);
        }

        if (texture != nullptr)
        {
            textureTGA = new char[strlen(texture) + 1];
            strcpy_s(textureTGA, strlen(texture ) + 1, texture);
        }
    }

    // Destructor
    ~TextureResource()
    {
        // Release dynamically allocated memory in the destructor
        delete[] type;
        delete[] textureTGA;
    }

};

