#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "Assets/Camera/FlyCamera.h"
#include "Gizmos.h"
#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "Loaders/ObjLoader/ObjectLoader.h"
#include "Tutorial4.h"

using namespace std;


Tutorial4::Tutorial4(Renderer* a_render)
{
	m_render = a_render;
}

Tutorial4::~Tutorial4()
{

}

void Tutorial4::ImageLoad()
{
	m_render->Generate2DObject();
	//DiffuseMapLoad();
	//NormalMapLoad();

}


void Tutorial4::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);

	int loc;
	//Actual Drawing
	glUseProgram(m_program);

	loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_normalmap);


	loc = glGetUniformLocation(m_program, "diffuse");
	glUniform1i(loc, 0);

	loc = glGetUniformLocation(m_program, "normal");
	glUniform1i(loc, 1);




	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tutorial4::GameLoop()
{

}
