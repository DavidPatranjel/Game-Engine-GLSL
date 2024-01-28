#pragma once
class ModelResource
{
public:
	int idModel;
	char *modelNFG;

public:
    // Constructor
    ModelResource(int id, const char* model)
        : idModel(id), modelNFG(nullptr)
    {
        if (model != nullptr)
        {
            modelNFG = new char[strlen(model) + 1];
            strcpy_s(modelNFG, strlen(model) + 1, model);
        }
    }

    // Destructor
    ~ModelResource()
    {
        // Release dynamically allocated memory in the destructor
        delete[] modelNFG;
    }

	
};

