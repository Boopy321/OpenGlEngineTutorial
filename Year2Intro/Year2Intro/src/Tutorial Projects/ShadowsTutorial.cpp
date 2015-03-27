#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "ShadowsTutorial.h"
#include "Assets\RenderTargets\RenderTarget.h"
#include <glm\glm.hpp>
#include "Assets\Render\Renderer.h"
#include "Gizmos.h"
#include "Assets\Camera\FlyCamera.h"
#include "FBXFile.h"

ShadowsTutorial::ShadowsTutorial(Renderer* a_render)
{
	m_renderScreen = new RenderTarget(2048, 2048,1);
	m_render = a_render;
	CreateLight(); 
	m_render->LoadFBX("./data/models/FemaleBladenSoul.FBX");
	
	m_lightDir = glm::vec3(0.75, 0.5, 0.75);
	m_render->Generate2DObject();
}


ShadowsTutorial::~ShadowsTutorial()
{
}

void ShadowsTutorial::CreateLight()
{
	m_lightDirection = glm::normalize(glm::vec3(1, 2.5f, 1));

	lightProjection = glm::ortho<float>(-100, 100,
		-100, 100, -100, 100);

	 lightView = glm::lookAt(m_lightDirection,
		glm::vec3(0), glm::vec3(0, 1, 0));

	

}

void ShadowsTutorial::Draw(FlyCamera &_gameCamera, float a_deltatime)
{

	m_lightMatrix = lightProjection * lightView;
	glm::mat4 projectionView = _gameCamera.getProjectionView();


	//Shadow Pass:Bind our shadow map target and clear the depth
	m_renderScreen->BindTarget();
	glClear(GL_DEPTH_BUFFER_BIT);

	unsigned int m_program = m_render->ReturnProgramShadowMap();
	glUseProgram(m_program);

	int loc(glGetUniformLocation(m_program, "LightMatrix"));
	glUniformMatrix4fv(loc, 1, GL_FALSE, &(m_lightMatrix[0][0]));
	//Called in the render class
	// bind the light matrix
	m_render->FBXDraw();
	

	//----------------------------------------------------
	m_renderScreen->BindBackBuffer();
	glViewport(0,0,1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//SHADOW CODE---------------------
	glm::mat4 textureSpaceOffset(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
		);
	glm::mat4 lightMatrix = textureSpaceOffset * m_lightMatrix;	m_program = m_render->ReturnProgramShadow();
	glUseProgram(m_program);

	loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &projectionView[0][0]);

	loc = glGetUniformLocation(m_program, "shadowBias");
		glUniform1f(loc, 0.01f);

	loc = glGetUniformLocation(m_program, "LightMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &lightMatrix[0][0]);

	loc = glGetUniformLocation(m_program, "LightDir");
	glUniform3fv(loc, 1, &m_lightDirection[0]);
	
	m_renderScreen->BindTexture();
	
	loc = glGetUniformLocation(m_program, "shadowMap");
	glUniform1i(loc, 0);

	//m_program = m_render->ReturnProgramMap();
	//glUseProgram(m_program);

	//loc = glGetUniformLocation(m_program, "ProjectionView");
	//glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);


	//m_render->MapTexture();
	//
	//loc = glGetUniformLocation(m_program, "diffuse");
	//glUniform1i(loc, 0);

	//loc = glGetUniformLocation(m_program, "normal");
	//glUniform1i(loc, 1);


	//loc = glGetUniformLocation(m_program, "LightDir");
	//glUniform3fv(loc, 1, &m_lightDirection[0]);

	//Draws the cube
	
	m_render->FBXDraw();
	//----------------------

	glBindVertexArray(m_render->m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ShadowsTutorial::GameLoop()
{

}

void ShadowsTutorial::AddstuffTwBar(TwBar* a_bar)
{
	TwAddVarRW(a_bar, "Shadow Control",
		TW_TYPE_DIR3F, &lightView, "");

	TwAddVarRW(a_bar, "Light Direction",
		TW_TYPE_DIR3F, &m_lightDirection[0], "");

}

