#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include "Tutorial3.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <stb_image.h>
#include "Assets\Camera\FlyCamera.h"
#include "Gizmos.h"
#include "Application.h"
#include "Loaders\ObjLoader\ObjectLoader.h"
#include <AntTweakBar.h>
#include "Assets\CpuParticle\ParticleEmittor.h"
#include "Assets\RenderTargets\RenderTarget.h"
#include "Assets\Render\Renderer.h"
#include <assert.h>
#include "Assets\GpuParticle\GpuParticleEmitter.h"

using namespace std;


Tutorial3::Tutorial3(Renderer* a_render)
{
	m_render = a_render;
	m_emitter = new GPUParticleEmitter(a_render);
	m_emitter->initalise(100000,
		0.1f, 5.0f,
		5, 20,
		1, 0.1f,
		glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 1));
}

Tutorial3::~Tutorial3()
{
}

void Tutorial3::ImageLoad()
{
	indexData = m_render->LoadObject("./data/models/bunny");
	/*assert(indexData > 0);*/
	//Actually Create a light fvalue
	m_lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_lightDir = glm::vec3(0.f, 0.f, 1.0f);
	m_spec = 8;
}

void Tutorial3::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);
	unsigned int m_program = m_render->ReturnProgramObject();

	//Actual Drawing
	glUseProgram(m_program);
	assert(m_program > 0);

	int loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);

	loc = glGetUniformLocation(m_program, "LightDir");
	glUniform3f(loc, m_lightDir.x,m_lightDir.y,m_lightDir.z);
	
	loc = glGetUniformLocation(m_program, "LightColour");
	glUniform3f(loc, m_lightColour.x, m_lightColour.y, m_lightColour.z);

	loc = glGetUniformLocation(m_program, "CameraPos");
	glUniform3f(loc, _gameCamera.GetPosition().x, _gameCamera.GetPosition().y, _gameCamera.GetPosition().z);

	loc = glGetUniformLocation(m_program, "SpecPow");
	glUniform1f(loc, m_spec);

	glBindVertexArray(m_render->m_VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render->m_IBO);
	
	glDrawElements(GL_TRIANGLES, indexData , GL_UNSIGNED_INT, 0);

	m_emitter->draw((float)glfwGetTime(),
		_gameCamera.getWorldTransform(),
		_gameCamera.getProjectionView());
}

void Tutorial3::GameLoop()
{
}

void Tutorial3::AddVarToTwBar(TwBar* a_bar)
{
	//Add the variables for Tweak bar
	TwAddVarRW(a_bar, "Light Colour",
		TW_TYPE_COLOR3F, &m_lightColour[0], "");

	TwAddVarRW(a_bar, "Light Direction",
		TW_TYPE_DIR3F, &m_lightDir[0], "");

	TwAddVarRW(a_bar, "Specular Power",
		TW_TYPE_FLOAT, &m_spec, "");
}

