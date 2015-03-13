#pragma once

class FlyCamera;

class TutorialBaseClass
{
public:

	virtual void Draw(FlyCamera &_gameCamera, float a_deltatime) = 0;
	virtual void GameLoop() = 0;
};

