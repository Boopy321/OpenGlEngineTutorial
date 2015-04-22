#include "Trees.h"
#include "Assets\FBXModel\FBXModel.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Assets\Light\Light.h"
#include "Assets\AntTweakBar\AntTweakBar.h"

Tree::Tree(AntTweakBar* a_bar)
{
	m_worldtransform = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2, glm::vec3(-1, 0, 0));
	
}	

Tree::~Tree()
{
}

void Tree::Draw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera)
{
	///glm::mat4 transform = glm::scale(glm::vec3(0.1f, 0.1f, 0.1f));
   //
	//transform = glm::translate(transform, glm::vec3(m_worldtransform[3].xyz));
   //
	m_model->SetTransform(m_worldtransform);
	m_model->FBXDraw(a_program,a_render,a_light,_gameCamera, m_worldtransform );
}

void Tree::SetPosition(glm::vec3& a_position)
{
	m_worldtransform[3] = glm::vec4(a_position, 1);
}

void Tree::SetModel(FBXModel* a_model)
{
	 m_model = a_model;
}

void Tree::SetScale(glm::vec3 a_scale)
{
	glm::mat4 scale = glm::scale(a_scale);
	m_worldtransform = m_worldtransform * scale;
}

void Tree::SetRotate(glm::vec3 a_angle)
{
	glm::mat4 rot = glm::rotate(m_worldtransform, glm::pi<float>() / 2, a_angle);
	m_worldtransform = m_worldtransform * rot;
}

