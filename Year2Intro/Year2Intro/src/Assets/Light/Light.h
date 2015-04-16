#pragma once
#include <glm\glm.hpp>
class AntTweakBar;
class Light
{
public:
	Light(AntTweakBar* a_bar);
	~Light();

	inline glm::vec3 getLightDir(){ return m_lightDirection; };
	inline glm::vec3 getDiffuse(){ return m_diffuse; };
	inline glm::vec3 getSpecularVec3(){ return Specular; };
	inline float getSpec(){ return m_spec; };

	glm::vec3 m_lightDirection;

	void Update();
	static void ReverseLight();
private:

	glm::vec3 m_diffuse;
	glm::vec3 Specular;
	float m_spec;
	static bool reverse;
};

