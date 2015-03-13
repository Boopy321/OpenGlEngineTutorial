#pragma once

class Renderer;
class ParticleEmittor;
#include "TutorialBaseClass.h"

class Tutorial5 : public TutorialBaseClass
{
public:
	Tutorial5();
	Tutorial5(Renderer* a_render);
	~Tutorial5();

	void ImageLoad();
	//Must Contain the Current Game Camera and Deltatime
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();
	void Update();


private:

	glm::vec3 m_lightDir;
	glm::vec3 m_lightColour;

	float m_spec;

	ParticleEmittor* m_particles;

	Renderer* m_render;
	unsigned int m_program;
};

