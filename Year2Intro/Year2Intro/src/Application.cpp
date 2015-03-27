#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Assets\InputManager\InputManager.h"

Application::Application()
{
	
}

bool Application::startUp()
{
	if (glfwInit() == false)
		return false;
		
		window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);
		
		
		if (window == nullptr)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
		{
			glfwDestroyWindow(window);
			glfwTerminate();
			return false;
		}
		
		_gameCamera.SetInputWindow(window);		
		
		//Load Render into Tutorial
		m_render = new Renderer();
		CurrentProject = new ShadowsTutorial(m_render);
		
		//AntTweakbar stuff
		TwInit(TW_OPENGL_CORE, nullptr);
		TwWindowSize(1280, 720);
		m_keyManager.AntBarCallbacks(window);
		m_bar = TwNewBar("This is the bar");

		TwAddVarRW(m_bar, "Clear Colour",
			TW_TYPE_COLOR4F, &m_clearColour[0], "");

		m_clearColour = vec4(0.75f,0.75f,0.75f,1.0f);
		_gameCamera.AddCamSpeedToTwBar(m_bar);
		/*CurrentProject->AddVarToTwBar(m_bar);*/
		CurrentProject->AddstuffTwBar(m_bar);
		//CurrentProject->ImageLoad()*/;
		return true;
}

void Application::update(float deltatime)
{
	// Red/ Green/Blue
	glClearColor(m_clearColour.x, m_clearColour.y, m_clearColour.z,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	CurrentProject->GameLoop();
	//Camera
	_gameCamera.update(deltatime);
	//Current Games Draw
	draw(deltatime);

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void Application::draw(float a_deltatime)
{	
	
	Gizmos::clear();
	CurrentProject->Draw(_gameCamera,a_deltatime);
	Gizmos::draw(_gameCamera.getProjectionView());
	TwDraw();
}

void Application::shutdown()
{
	/*CurrentProject.cleanupOpenGlBuffers();*/
	TwDeleteAllBars();
	TwTerminate();
	glfwDestroyWindow(window);
	glfwTerminate();
}

Application::~Application()
{
}

void Application::run()
{
	//IF the startup fails. Dont load the program
	
	if (startUp() == false)
		return;
		
		//Stats up Gizmos Shape Creation code
		Gizmos::create();
		//m_render->GenerateGrid(100, 100);

		//allows Depth varible to be used
		glEnable(GL_DEPTH_TEST);
		
		while (glfwWindowShouldClose(window) == false &
		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
		{
			//Deltatime stuff
			float currentTime = (float)glfwGetTime();
			float deltatime = currentTime - previousTime; 
			previousTime = currentTime;	
			update(deltatime);	
		}

		shutdown();
}


