#pragma once

typedef struct CTwBar TwBar;
#include "GLFW\glfw3.h"
#include <string>

class AntTweakBar
{
public:
	AntTweakBar(int a_width, int a_height, GLFWwindow* a_window);
	~AntTweakBar();

	TwBar* m_bar;
	void AddVarToTwBar();
	void AntBarCallbacks(GLFWwindow* a_window);

	void Draw();
	
	void AddBoolToTwBar(std::string a_name, bool *a_bool);
	void AddFloatToTwBar(std::string a_name, float *a_var);
	void AddIntToTwBar(std::string a_name, int *a_var);
	void AddVec3ToTwBar(std::string a_name, glm::vec3 *a_vec3);
	void AddVec4ToTwBar(std::string a_name, glm::vec4 *a_vec4);
	

	void ChangeLightDir();
	void RegenerateTerrain();

	//To Call the generate function
	static void StaticFunction();
	
private:
	GLFWwindow* window; 
};

