#pragma once

#include "Assets\Planet(Sphere Code)\Planet.h"
#include "TutorialBaseClass.h"
#include "Assets\Render\Renderer.h"

class Tutoral1 : public TutorialBaseClass
{
public:
	Tutoral1();
	Tutoral1(Renderer* a_render);
	~Tutoral1();

	void Draw();
	void GameLoop();
	void ImageLoad();

private:
	Planet sun;
	Planet mercury;
	Planet venus;
	Planet earth;
	Planet e_moon;

	Renderer* m_render;
};

