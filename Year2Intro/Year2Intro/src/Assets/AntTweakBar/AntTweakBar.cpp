#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "AntTweakBar.h"
#include <string>
#include "Tutorial Projects\ProceduralGenTutorial.h"

AntTweakBar::AntTweakBar(int a_width, int a_height, GLFWwindow* a_window)
{
	TwInit(TW_OPENGL_CORE, nullptr);
	TwWindowSize(a_width, a_height);
	m_bar = TwNewBar("Tweak Bar");
	AntBarCallbacks(a_window);
}


void AntTweakBar::AntBarCallbacks(GLFWwindow* a_window)
{
	//Lamba bodys for callbacks
	auto OnMouseButton = [](GLFWwindow*, int b, int a, int m){TwEventMouseButtonGLFW(b, a); };
	auto OnMousePosition = [](GLFWwindow*, double x, double y){TwEventMousePosGLFW((int)x, (int)y); };
	auto OnMouseScroll = [](GLFWwindow*, double x, double y) {TwEventMouseWheelGLFW((int)y); };
	auto OnKey = [](GLFWwindow*, int k, int s, int a, int m) { TwEventKeyGLFW(k, a); };
	auto OnChar = [](GLFWwindow*, unsigned int c) {TwEventCharGLFW(c, GLFW_PRESS); };
	auto OnWindowResize = [](GLFWwindow*, int w, int h) {TwWindowSize(w, h); glViewport(0, 0, w, h);};
	//Callbacks for AntTweakbar
	glfwSetMouseButtonCallback(a_window, OnMouseButton);
	glfwSetCursorPosCallback(a_window, OnMousePosition);
	glfwSetScrollCallback(a_window, OnMouseScroll);
	glfwSetKeyCallback(a_window, OnKey);
	glfwSetCharCallback(a_window, OnChar);
	glfwSetWindowSizeCallback(a_window, OnWindowResize);


	window = a_window;
}

AntTweakBar::~AntTweakBar()
{
	TwDeleteAllBars();
	TwTerminate();
}

void AntTweakBar::Draw()
{
	TwDraw();
	
}
//Adding floats is cool
void AntTweakBar::AddFloatToTwBar(std::string a_name,float *a_var)
{
	//Add the variables for Tweak bar
	TwAddVarRW(m_bar,a_name.c_str(),
		TW_TYPE_FLOAT, a_var, "");

}
//For some reason we wanna deal with ints
void AntTweakBar::AddIntToTwBar(std::string a_name,int *a_var)
{
	//Add the variables for Tweak bar
	TwAddVarRW(m_bar, a_name.c_str(),
		TW_TYPE_INT32, a_var, "");

}

//Allows Vec3 Direction Vectors to be adjusted
void AntTweakBar::AddVec3ToTwBar(std::string a_name,glm::vec3 *a_vec3)
{
	//Add the variables for Tweak bar
	TwAddVarRW(m_bar, a_name.c_str(),
		TW_TYPE_DIR3F, a_vec3, "");

}
//COLOR ADJUSTMENTS ONLY
void AntTweakBar::AddVec4ToTwBar(std::string a_name,glm::vec4 *a_vec4)
{
	//Add the variables for Tweak bar
	TwAddVarRW(m_bar, a_name.c_str(),
		TW_TYPE_COLOR4F, a_vec4, "");

}

void AntTweakBar::AddBoolToTwBar(std::string a_name, bool *a_bool)
{
	//Add the variables for Tweak bar
	TwAddVarRW(m_bar, a_name.c_str(),
		TW_TYPE_BOOL32, a_bool, "");

}

void AntTweakBar::RegenerateTerrain()
{
	TwAddButton(m_bar, "Generate Terrain", 
	[](void* a_clientData){ProceduralGenTutorial::GenTerrain();},
	NULL, ""
	);
}


