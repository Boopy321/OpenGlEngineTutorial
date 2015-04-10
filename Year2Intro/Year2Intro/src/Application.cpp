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
#include "Assets\AntTweakBar\AntTweakBar.h"

Application::Application()
{
//Window Sizes So i stop killing myself
	m_wHeight = 720;
	m_wWidth = 1280;
	
}

bool Application::startUp()
{
	if (glfwInit() == false)
		return false;

		window = glfwCreateWindow(m_wWidth, m_wHeight, "Computer Graphics", nullptr, nullptr);

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
		std::cout << "OpenGL loaded" << std::endl;
		_gameCamera.SetInputWindow(window);		
		
		//Load Render into Tutorial
		m_render = new Renderer();
		//AntTweakbar stuff
		m_bar = new AntTweakBar(m_wWidth, m_wHeight, window);
		m_bar->AddVec4ToTwBar("ColorScheme", &m_clearColour);
		//Create the current Project
		CurrentProject = new ProceduralGenTutorial(m_render,m_bar);
		
		//Background color 
		m_clearColour = vec4(0.0f,0.0f,0.00f,1.0f);
	
		return true;
}

void Application::update(float a_deltatime)
{
	// Red/ Green/Blue
	glClearColor(m_clearColour.x, m_clearColour.y, m_clearColour.z,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	CurrentProject->GameLoop();
	//Camera
	_gameCamera.update(a_deltatime);
	//Current Games Draw
	draw(a_deltatime);

	glfwSwapBuffers(window);
	glfwPollEvents();

	m_frameElaspedtime += a_deltatime;

	if (m_frameElaspedtime > 1.0f)
	{
		m_frameElaspedtime = 0.0f;
		m_framerate = m_frameCounter;
		m_frameCounter = 0;
	}

}

void Application::draw(float a_deltatime)
{	
	m_frameCounter++;

	Gizmos::clear();
	CurrentProject->Draw(_gameCamera,a_deltatime);
	Gizmos::draw(_gameCamera.getProjectionView());
	m_bar->Draw();
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


