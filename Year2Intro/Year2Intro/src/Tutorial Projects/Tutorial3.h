#pragma once
class FlyCamera;

#include <vector>
#include "VertexStructure.h"
#include "AntTweakBar.h"
#include "TutorialBaseClass.h"
#include <GLFW\glfw3.h>

class Renderer;\
class ObjectLoader;

class Tutorial3 : public TutorialBaseClass
{
public:
	Tutorial3();
	Tutorial3(Renderer* a_render);
	~Tutorial3();

	void ImageLoad();
	//Must Contain the Current Game Camera and Deltatime
	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();

	void ShaderProgram();
	void AddVarToTwBar(TwBar* a_bar);
	void GetShaderProgram(GLuint a_program);

private:


	unsigned int m_texture;
	unsigned int indexData;

	int m_imageWidth, m_imageHeight, m_imageFormat;

	std::string m_path;
	glm::vec3 m_lightDir;
	glm::vec3 m_lightColour;
	
	Renderer* m_render;
	
	float m_spec;
};

