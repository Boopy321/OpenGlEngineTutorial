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
#include "Assets\Render\Renderer.h"
#include "Assets\Light\Light.h"
#include <iostream>

using namespace std;

void APIENTRY openglCallbackFunction(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{

	cout << "---------------------opengl-callback-start------------" << endl;
	cout << "message: " << message << endl;
	cout << "type: ";
	switch (type) {
	case GL_DEBUG_TYPE_ERROR:
		cout << "ERROR";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		cout << "DEPRECATED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		cout << "UNDEFINED_BEHAVIOR";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		cout << "PORTABILITY";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		cout << "PERFORMANCE";
		break;
	case GL_DEBUG_TYPE_OTHER:
		cout << "OTHER";
		break;
	}
	cout << endl;

	cout << "id: ";
	cout << "severity: ";
	switch (severity){
	case GL_DEBUG_SEVERITY_LOW:
		cout << "LOW";
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		cout << "MEDIUM";
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		cout << "HIGH";
		break;
	}
	cout << endl;
	cout << "---------------------opengl-callback-end--------------" << endl;
}


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

#if _DEBUG
		if (glDebugMessageCallback){
			cout << "Register OpenGL debug callback " << endl;
			//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(openglCallbackFunction, nullptr);
			GLuint unusedIds = 0;
			glDebugMessageControl(GL_DONT_CARE,
				GL_DONT_CARE,
				GL_DONT_CARE,
				0,
				&unusedIds,
				true);
		}
		else
			cout << "glDebugMessageCallback not available" << endl;
#endif

		_gameCamera.SetInputWindow(window);		
		
		//Load Render into Tutorial
		m_render = new Renderer();
		//AntTweakbar stuff
		m_bar = new AntTweakBar(m_wWidth, m_wHeight, window);
		m_bar->AddVec4ToTwBar("ColorScheme", &m_clearColour);
		//Create the current Project
		m_light = new Light(m_bar);
		
		CurrentProject = new ProceduralGenTutorial(m_render,m_bar,m_light);
		m_bar->AddFloatToTwBar("Framerate", &m_framerate);
		//Background color 
		m_clearColour = vec4(0.0f,0.0f,0.00f,1.0f);
	
		return true;
}

void Application::update(float a_deltatime)
{

	glClearColor(m_clearColour.x, m_clearColour.y, m_clearColour.z,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_light->Update();
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

		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//allows Depth varible to be used
		glEnable(GL_DEPTH_TEST);
		while (glfwWindowShouldClose(window) == false &&
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

