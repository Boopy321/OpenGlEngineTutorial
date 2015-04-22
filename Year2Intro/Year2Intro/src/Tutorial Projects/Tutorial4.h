#pragma once
class FlyCamera;

#include <vector>

#include "TutorialBaseClass.h"
#include "VertexStructure.h"
#include "Assets\Render\Renderer.h"
class ObjectLoader;

class Tutorial4 : public TutorialBaseClass
{
public:
	Tutorial4();
	Tutorial4(Renderer* a_render);
	~Tutorial4();

	void ImageLoad();
	//Must Contain the Current Game Camera and Deltatime
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();

	//Tutorial 4 Extras
	void ShaderProgram();
	//void DiffuseMapLoad();
	void NormalMapLoad();
	void Generate2DObject();

private:

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int m_texture;
	unsigned int m_program;
	unsigned int m_normalmap;

	Renderer* m_render;

	int m_imageWidth, m_imageHeight, m_imageFormat;
	std::string m_path;

};

