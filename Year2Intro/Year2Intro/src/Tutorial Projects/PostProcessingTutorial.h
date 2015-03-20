#pragma once

#include "Tutorial Projects\TutorialBaseClass.h"
class RenderTarget;
class Renderer;

class PostProcessingTutorial : public TutorialBaseClass
{
public:
	PostProcessingTutorial();
	PostProcessingTutorial(Renderer* a_render);
	~PostProcessingTutorial();
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();
	void QuadScreen();

private:
	RenderTarget* m_renderScreen;
	unsigned int m_vao;
	unsigned int m_vbo;
	Renderer* m_render;
	unsigned int m_fboTexture;
};

