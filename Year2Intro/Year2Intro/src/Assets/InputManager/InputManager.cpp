#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "InputManager.h"

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::Getkey(GLFWwindow* a_window, Keys a_key)
{
	return glfwGetKey(window, a_key);
}

bool InputManager::GetMouseDown(int a_mouseButton)
{
	return glfwGetMouseButton(window, a_mouseButton);
}
