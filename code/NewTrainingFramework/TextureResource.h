#pragma once
class TextureResource
{
public:
	int idTexture;
	char *type;
	char *textureTGA, * minFilter, * magFilter, * wrapS, * wrapT;

public:
    // Constructor
    TextureResource(int id, const char* t, const char *texture, 
        const char* minf, const char *magf, const char *wraps, const char *wrapt)
        : idTexture (id), type(nullptr), textureTGA(nullptr), minFilter(nullptr), 
        magFilter(nullptr), wrapS(nullptr), wrapT(nullptr)
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

        if (minf != nullptr)
        {
            minFilter = new char[strlen(minf) + 1];
            strcpy_s(minFilter, strlen(minf) + 1, minf);
        }

        if (magf != nullptr)
        {
            magFilter = new char[strlen(magf) + 1];
            strcpy_s(magFilter, strlen(magf) + 1, magf);
        }

        if (wraps != nullptr)
        {
            wrapS = new char[strlen(wraps) + 1];
            strcpy_s(wrapS, strlen(wraps) + 1, wraps);
        }

        // Allocate memory for modelVS and modelFS and copy the strings
        if (wrapt != nullptr)
        {
            wrapT = new char[strlen(wrapt) + 1];
            strcpy_s(wrapT, strlen(wrapt) + 1, wrapt);
        }
    }

    // Destructor
    ~TextureResource()
    {
        // Release dynamically allocated memory in the destructor
        delete[] type;
        delete[] textureTGA;
        delete[] minFilter;
        delete[] magFilter;
        delete[] wrapS;
        delete[] wrapT;
    }

};

