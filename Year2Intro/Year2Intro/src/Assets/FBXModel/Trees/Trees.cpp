#include "Trees.h"
#include "Assets\FBXModel\FBXModel.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Assets\Light\Light.h"
#include "Assets\AntTweakBar\AntTweakBar.h"

Tree::Tree(AntTweakBar* a_bar)
{
	glm::vec3 Rotate = glm::vec3(glm::vec3(0, 1, 0));
	m_worldtransform = glm::scale(glm::vec3(0.1, 0.1, 0.1)); // scale
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2,Rotate);//Rotate
}

Tree::~Tree()
{

}

void Tree::Draw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera)
{
	m_model->FBXDraw(a_program,a_render,a_light,_gameCamera,m_worldtransform );
	
}

void Tree::SetPosition(glm::vec3& a_position)
{
	m_worldtransform[3] = glm::vec4(a_position, 1);
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2, glm::vec3(glm::vec3(0, 1, 0)));//Rotate
}

void Tree::SetModel(FBXModel* a_model)
{
	 m_model = a_model;
}

void Tree::SetScale(glm::vec3 a_scale)
{
	m_worldtransform = glm::scale(a_scale);
}

void Tree::SetTransform(glm::mat4 a_transform)
{
	m_worldtransform = a_transform;
}