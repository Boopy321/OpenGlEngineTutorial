#pragma once
class RenderTarget;
class Renderer;
#include <glm\glm.hpp>
class FlyCamera;
#include <AntTweakBar.h>
class FBXModel;

class ShadowsTutorial
{
public:
	ShadowsTutorial(Renderer* a_render);
	~ShadowsTutorial();

	void CreateLight();
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();

	void AddstuffTwBar(TwBar* a_bar);
	void QuadScreen();
private:

	RenderTarget* m_renderScreen;
	Renderer* m_render;

	glm::vec3 m_lightDirection;
	glm::mat4 m_lightMatrix;
	glm::vec3 m_lightDir;
	glm::vec3 m_lightColour;
	
	glm::mat4 lightProjection;
	glm::mat4 lightView;

	unsigned int m_vao;
	unsigned int m_vbo;
	
	float m_spec;

	FBXModel* m_dragon;
};

