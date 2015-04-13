//#include "gl_core_4_4.h"
//#include "GLFW\glfw3.h"
//#include "Assets\Camera\FlyCamera.h"
//#include "Tutorial5.h"
//#include <FBXFile.h>
//#include "Assets\Render\Renderer.h"
//#include <assert.h>
//
//
//Tutorial5::Tutorial5()
//{
//	
//}
//
//Tutorial5::Tutorial5(Renderer* a_render)
//{
//	m_render = a_render;
//	
//}
//
//Tutorial5::~Tutorial5()
//{
//	m_render->Close();
//}
//
//void Tutorial5::ImageLoad()
//{
//
//}
//
//void Tutorial5::Draw(FlyCamera &_gameCamera, float a_deltatime)
//{
//	unsigned int program = m_render->ReturnProgramObject();
//	glUseProgram(program);
//
//	int loc = glGetUniformLocation(program, "ProjectionView");
//	assert(loc >= 0);
//	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);
//
//	loc = glGetUniformLocation(program, "LightDir");
//	assert(loc >= 0);
//	glUniform3f(loc, m_lightDir.x, m_lightDir.y, m_lightDir.z);
//
//	loc = glGetUniformLocation(program, "LightColour");
//	assert(loc >= 0);
//	glUniform3f(loc, m_lightColour.x, m_lightColour.y, m_lightColour.z);
//
//	loc = glGetUniformLocation(program, "CameraPos");
//	assert(loc >= 0);
//	glUniform3f(loc, _gameCamera.GetPosition().x, _gameCamera.GetPosition().y, _gameCamera.GetPosition().z);
//
//	loc = glGetUniformLocation(program, "SpecPow");
//	assert(loc >= 0);
//	glUniform1f(loc, m_spec);
//		
//	
//	m_render->FBXDraw();
//	
//}
//
//void Tutorial5::Update(){
//	
//}
//
//void Tutorial5::GameLoop()
//{
//}
//
