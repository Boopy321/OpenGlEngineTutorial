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
	m_parTime = -5;

	m_speed = 0.1f;
	m_render = a_render;
	m_emitter = new GPUParticleEmitter(a_render);
	

//m_emitter->initalise(1000000,
//	0.01f, 3.f,
//	0.01f, 5,
//	0.1, 0.0001f,
//	glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 0, 0));
//
//m_emitterReverse->initalise(1000000,
//	0.01f, 0.9f,
//	0.01f, 5,
//	0.1, 0.0001f,
//	glm::vec4(0.75, 0.75, 0.75, 0.4), glm::vec4(0.25, 0.25, 0.25, 1));
	//m_AltScreen = new RenderTarget(512,512);
	/*GenMesh();*/
}

Tutorial3::~Tutorial3()
{
}

void Tutorial3::ImageLoad()
{
	/*indexData = m_render->LoadObject("./data/models/bunny");*/

	/*assert(indexData > 0);*/
	//Actually Create a light fvalue
	m_lightColour = glm::vec3(1.0f, 1.0f, 1.0f);
	m_lightDir = glm::vec3(0.f, 0.f, 1.0f);
	m_spec = 8;
	
}

void Tutorial3::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);
	
	//Bind the framebuffer
	// Bind FBO
	// Render stuff to FBO texture here
	// Bind backbuffer
	// Shader bind for each type of mesh
	// Render stuff and FBO texture on plane

	////m_AltScreen->BindTarget();

	//
	//glClearColor(1.f, 1.f, 1.f, 1);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Gizmos::draw(_gameCamera.getProjectionView());

	//
	////Unbind Framebuffer
	//m_AltScreen->BindBackBuffer();

	//------------------------------------------------------

	glViewport(0, 0, 1280, 900);

	/*DoStuff(_gameCamera);*/

	int m_program = m_render->ReturnProgramObject();
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

	AdjustParTime();
	if (m_increment == true)
		m_parTime += 0.1f;
	else
		m_parTime -= 0.1f;

	m_emitterReverse->draw(m_parTime, (float)glfwGetTime(),
		_gameCamera.getWorldTransform(),
		_gameCamera.getProjectionView());
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/
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

void Tutorial3::GenMesh()
{
	float vertexData[] = {
		-5, 0, -5, 1, 0, 0,
		5, 0, -5, 1, 1, 0,
		5, 10, -5, 1, 1, 1,
		-5, 10, -5, 1, 0, 1,
	};
	unsigned int indexData[] = {
		0, 1, 2,
		0, 2, 3,
	};
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 6 * 4,
		vertexData, GL_STATIC_DRAW);
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* 6,
		indexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, ((char*)0) + 16);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Tutorial3::DoStuff(FlyCamera &_gameCamera)
{
	unsigned int m_program = m_render->ReturnProgram();

	glUseProgram(m_program);

	int loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE,
		&_gameCamera.getProjectionView()[0][0]);

	m_AltScreen->BindTexture();

	glUniform1i(glGetUniformLocation(m_program, "diffuse"), 0);
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Tutorial3::AdjustParTime()
{
	if (m_parTime >= 10 && m_parTime >= 0)
		m_increment = false;
	else if (m_parTime <= -10 && m_parTime <= 0)
		m_increment = true;
}
