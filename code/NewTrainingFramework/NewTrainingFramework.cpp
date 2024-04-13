// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "../Utilities/TGA.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include "Vertex.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Globals.h"
#define PI 3.141592
using namespace rapidxml;

const char* resourceManagerFileXML = "../../textures/resourceManager.xml";
const char* sceneManagerFileXML = "../../textures/sceneManager.xml";

int TWidth, THeight, TBBP;


int Init ( ESContext *esContext )
{
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );
	glEnable(GL_DEPTH_TEST);
	
	///resource manager
	ResourceManager* resourceManager = ResourceManager::getInstance();
	resourceManager->Init(resourceManagerFileXML);
	SceneManager* sceneManager = SceneManager::getInstance();
	sceneManager->Init(sceneManagerFileXML);
	return 0;
}

void Draw ( ESContext *esContext )
{
	SceneManager::getInstance()->Draw(esContext);
}

void Update ( ESContext *esContext, float deltaTime )
{
	SceneManager::getInstance()->Update(deltaTime);	
}

void MouseEvent(ESContext* esContext, MouseButtons btn, MouseEvents event, int x, int y)
{
	printf("Mouse position %d %d \n", x, y);
	switch (btn)
	{
	case LEFT_CLICK:
		printf("LEFT CLICK ");
		switch (event)
		{
		case MOUSE_CLICK:
			printf("MOUSE CLICK \n");
			break;
		case MOUSE_DOUBLE_CLICK:
			printf("MOUSE DOUBLE CLICK \n");
			break;
		case MOUSE_DOWN:
			printf("MOUSE DOUWN \n");
			break;
		case MOUSE_UP:
			printf("MOUSE UP \n");
			break;
		default:
			break;
		}
		break;

	case RIGHT_CLICK:
		printf("RIGHT CLICK ");
		switch (event)
		{
		case MOUSE_CLICK:
			printf("MOUSE CLICK \n");
			break;
		case MOUSE_DOUBLE_CLICK:
			printf("MOUSE DOUBLE CLICK \n");
			break;
		case MOUSE_DOWN:
			printf("MOUSE DOUWN \n");
			break;
		case MOUSE_UP:
			printf("MOUSE UP \n");
			break;
		default:
			break;
		}

	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	SceneManager* sceneManager = SceneManager::getInstance();
	if (key == sceneManager->keyboardInput->Q ||
		key == sceneManager->keyboardInput->q)
	{
		printf("Q ");
		sceneManager -> moveActiveCameraOY(1);
	}
	else if (key == sceneManager->keyboardInput->W ||
		key == sceneManager->keyboardInput->w)
	{
		printf("W ");
		sceneManager->moveActiveCameraOZ(-1);
	}
	else if (key == sceneManager->keyboardInput->A ||
		key == sceneManager->keyboardInput->a)
	{
		printf("A ");
		sceneManager->moveActiveCameraOX(-1);
	}
	else if (key == sceneManager->keyboardInput->S ||
		key == sceneManager->keyboardInput->s)
	{
		printf("S ");
		sceneManager->moveActiveCameraOZ(1);
	}
	else if (key == sceneManager->keyboardInput->D ||
		key == sceneManager->keyboardInput->d)
	{
		printf("D ");
		sceneManager->moveActiveCameraOX(1);
	}
	else if (key == sceneManager->keyboardInput->E ||
		key == sceneManager->keyboardInput->e)
	{
		printf("E ");
		sceneManager->moveActiveCameraOY(-1);
	}

	

	switch(key)
	{
	case 'o':
	case 'O':
		printf("O ");
		sceneManager->rotateActiveCameraOZ(1);
		break;
	case 'p':
	case 'P':
		printf("P ");
		sceneManager->rotateActiveCameraOZ(-1);
		break;
	case VK_UP:
		printf("UP ");
		sceneManager->rotateActiveCameraOX(1);
		break;
	case VK_DOWN:
		printf("DOWN ");
		sceneManager->rotateActiveCameraOX(-1);
		break;
	case VK_LEFT:
		printf("LEFT ");
		sceneManager->rotateActiveCameraOY(1);
		break;
	case VK_RIGHT:
		printf("RIGHT ");
		sceneManager->rotateActiveCameraOY(-1);
		break;
	default:
		break;
	}
}

void CleanUp()
{
	SceneManager::getInstance()->freeResources();
	ResourceManager::getInstance()->freeResources();
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext; //main class for graphics

    esInitContext ( &esContext ); //init OPENGL ES (make calls after this f)

	esCreateWindow ( &esContext, "MakeR", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);
	esRegisterMouseFunc (&esContext, MouseEvent);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

