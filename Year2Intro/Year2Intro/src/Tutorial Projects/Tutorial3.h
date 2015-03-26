#pragma once
class FlyCamera;

#include <vector>
#include "VertexStructure.h"
#include "TutorialBaseClass.h"
#include <GLFW\glfw3.h>
class GPUParticleEmitter;
class Renderer;
class RenderTarget;
#include <AntTweakBar.h>
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
	void GenMesh();
	void DoStuff(FlyCamera &_gameCamera);
	void AdjustParTime();

private:
	unsigned int m_vbo, m_vao, m_ibo;
	unsigned int m_texture;
	unsigned int indexData;
	float m_parTime;
	bool m_increment;
	float m_speed;

	int m_imageWidth, m_imageHeight, m_imageFormat;

	std::string m_path;
	glm::vec3 m_lightDir;
	glm::vec3 m_lightColour;
	
	GPUParticleEmitter* m_emitter;
	GPUParticleEmitter* m_emitterReverse;
	Renderer* m_render;
	RenderTarget* m_AltScreen;

	float m_spec;
};

