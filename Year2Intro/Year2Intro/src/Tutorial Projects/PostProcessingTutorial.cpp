#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "PostProcessingTutorial.h"
#include "Assets\RenderTargets\RenderTarget.h"
#include <glm\glm.hpp>
#include "Assets\Render\Renderer.h"
#include "Gizmos.h"


PostProcessingTutorial::PostProcessingTutorial(Renderer* a_render)
{
	m_renderScreen = new RenderTarget(1280, 720,100);
	m_render = a_render;
	QuadScreen();
}


PostProcessingTutorial::~PostProcessingTutorial()
{

}

void PostProcessingTutorial::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);
	m_renderScreen->BindTarget();
	
	int m_program = m_render->ReturnProgramPostProcess();
	// clear the target
	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// draw our 3D scene
	Gizmos::addSphere(glm::vec3(1, 5, 1), 2, 10, 10, glm::vec4(1, 0, 0, 1));
	Gizmos::addSphere(glm::vec3(1, 0, 1), 2, 10, 10, glm::vec4(1, 0, 0, 1));

	Gizmos::draw(_gameCamera.getProjectionView());
	// bind the back-buffer
	//-------------------------------
	m_renderScreen->BindBackBuffer();
	glViewport(0, 0, 1280, 720);

	// gizmos for now
	m_renderScreen->BindTexture();
	// just clear the back-buffer depth as
	// each pixel will be filled
	glClear(GL_DEPTH_BUFFER_BIT);
	// draw out full-screen quad
	glUseProgram(m_program);

	m_renderScreen->BindTexture();
	int loc = glGetUniformLocation(m_program, "target");

	glUniform1i(loc, 0);
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void PostProcessingTutorial::GameLoop()
{

}

void PostProcessingTutorial::QuadScreen()
{
	glm::vec2 halfTexel = 1.0f / glm::vec2(1280, 720) * 0.5f;

	float vertexData[] = {
		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y,
		-1, 1, 0, 1, halfTexel.x, 1 - halfTexel.y,
		-1, -1, 0, 1, halfTexel.x, halfTexel.y,
		1, -1, 0, 1, 1 - halfTexel.x, halfTexel.y,
		1, 1, 0, 1, 1 - halfTexel.x, 1 - halfTexel.y,
	};

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 6 * 6,
		vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(float)* 6, ((char*)0) + 16);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}