#pragma once

#include "TutorialBaseClass.h"
#include "Assets\Render\Renderer.h"

class Tutorial2 : public TutorialBaseClass
{
public:
	Tutorial2();
	Tutorial2(Renderer* a_render);
	~Tutorial2();

	//Must Contain the Current Game Camera and Deltatime
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();

	//Tutorial 2 Base Stuff
	void GenerateGrid(unsigned int rows, unsigned int cols);
	void ShaderProgram();



protected:

	Renderer* m_render;

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_rows;
	unsigned int m_cols;
	unsigned int m_programID;

};

