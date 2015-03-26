#pragma once

struct GLFWwindow;


#include "Tutorial Projects/Tutoral1.h"
#include "Tutorial Projects/Tutorial2.h"
#include "Tutorial Projects/Tutorial3.h"
#include "Tutorial Projects/Tutorial4.h"
#include "Tutorial Projects/Tutorial5.h"
#include "Tutorial Projects\PostProcessingTutorial.h"
#include "Tutorial Projects\ShadowsTutorial.h"
#include "Assets/Camera/FlyCamera.h"
#include <AntTweakBar.h>
#include "Assets/InputManager/InputManager.h"
#include "Loaders/TinyObjLoader/tiny_obj_loader.h"
#include "Loaders/TinyObjLoader/TinyObjSideProject.h"


//Global space so any project can use AntTweakBar


class Application
{
public:
	Application();
	~Application();
	void run();

protected:

	GLFWwindow* window;
	float previousTime;
	FlyCamera _gameCamera;

private:
	bool startUp();

	void update(float deltatime);
	void draw(float a_deltatime);
	void shutdown();

	TwBar* m_bar;

	ShadowsTutorial* CurrentProject;

	InputManager m_keyManager;

	unsigned int m_ProgramID;

	glm::vec4 m_clearColour;

	Renderer* m_render;
};

