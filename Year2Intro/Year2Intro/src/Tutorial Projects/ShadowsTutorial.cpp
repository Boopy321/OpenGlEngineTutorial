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
	m_renderScreen = new RenderTarget(1024, 1024,1);
	m_render = a_render;
	CreateLight(); 
	m_render->LoadFBX("./data/models/bunny.fbx");
	m_lightDir = glm::vec3(0.75, 0.5, 0.75);
	m_render->Generate2DObject();
}


ShadowsTutorial::~ShadowsTutorial()
{
}

void ShadowsTutorial::CreateLight()
{
	m_lightDirection = glm::normalize(glm::vec3(1, 2.5f, 1));

	glm::mat4 lightProjection = glm::ortho<float>(-10, 10,
		-10, 10, -10, 10);

	glm::mat4 lightView = glm::lookAt(m_lightDirection,
		glm::vec3(0), glm::vec3(0, 1, 0));

	m_lightMatrix = lightProjection * lightView;

}

void ShadowsTutorial::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	
	//Shadow Pass:Bind our shadow map target and clear the depth
	m_renderScreen->BindTarget();
	glClear(GL_DEPTH_BUFFER_BIT);

	unsigned int m_program = m_render->ReturnProgramShadow();
	glUseProgram(m_program);
	int loc(glGetUniformLocation(m_program, "LightMatrix"));
	glUniformMatrix4fv(loc, 1, GL_FALSE, &(m_lightMatrix[0][0]));
	//Called in the render class
	// bind the light matrix
	m_render->FBXDraw();
	

	//----------------------------------------------------
	m_renderScreen->BindBackBuffer();
	glViewport(0,0,1280, 720);
	glClear(GL_COLOR_BUFFER_BIT || GL_DEPTH_BUFFER_BIT);


	//SHADOW CODE---------------------
	glm::mat4 textureSpaceOffset(
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
		);
	glm::mat4 lightMatrix = textureSpaceOffset * m_lightMatrix;	m_program = m_render->ReturnProgramShadowMap();

	loc = glGetUniformLocation(m_program, "LightMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &lightMatrix[0][0]);

	loc = glGetUniformLocation(m_program, "lightDir");
	glUniform3fv(loc, 1, &m_lightDirection[0]);

	loc = glGetUniformLocation(m_program, "shadowMap");
	glUniform1i(loc, 0);

	m_renderScreen->BindTexture();

	
	
	
	//FBX MODEL -------------
	m_program = m_render->ReturnProgramFbx();
	glUseProgram(m_program);

	loc = glGetUniformLocation(m_program, "ProjectionView");
	assert(loc >= 0);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);

	loc = glGetUniformLocation(m_program, "LightDir");
	assert(loc >= 0);
	glUniform3f(loc, m_lightDir.x, m_lightDir.y, m_lightDir.z);
	//Draws the cube

	m_render->FBXDraw();
	//----------------------
	

	m_renderScreen->BindTexture();


	glBindVertexArray(m_render->m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void ShadowsTutorial::GameLoop()
{

}

void ShadowsTutorial::AddstuffTwBar(TwBar* a_bar)
{
	TwAddVarRW(a_bar, "Light Direction",
		TW_TYPE_DIR3F, &m_lightDir[0], "");
}

void ShadowsTutorial::QuadScreen()
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