#pragma once
#include <glm\glm.hpp>
class AntTweakBar;
class Light
{
public:
	Light(AntTweakBar* a_bar);
	~Light();

	glm::vec3 m_lightDirection;
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 Specular;
	float m_spec;

	void Update();
	static void ReverseLight();
private:

	static bool reverse;
};

