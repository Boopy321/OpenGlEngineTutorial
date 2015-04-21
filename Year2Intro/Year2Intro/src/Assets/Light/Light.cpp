#include "Light.h"
#include <glm\glm.hpp>
#include "Assets\AntTweakBar\AntTweakBar.h"
bool Light::reverse(true);

Light::Light(AntTweakBar* a_bar)
{
	m_lightDirection = glm::vec3(0, 1, 0);
	m_diffuse = glm::vec3(0.4, 0.4, 0.4);
	m_ambient = glm::vec3(1);
	m_spec = 64.0f;
	a_bar->ChangeLightDir();

	a_bar->AddFloatToTwBar("Spec Float", &m_spec);
	a_bar->AddVec3ToTwBar("Diffuse", &m_diffuse);
	a_bar->AddVec3ToTwBar("Ambient", &m_ambient);
}


Light::~Light()
{
}

void Light::Update()
{
	
	if (reverse)
	{
		m_lightDirection = -glm::vec3(0, sin(glfwGetTime()), cos(glfwGetTime()));
	}
	else
	{
		m_lightDirection = -glm::vec3(0, cos(glfwGetTime()), sin(glfwGetTime()));
	}
}

void Light::ReverseLight()
{
	if (reverse)
		reverse = false;
	else if (!reverse)
		reverse = true;
}
