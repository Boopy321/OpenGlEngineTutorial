#include "Trees.h"
#include "Assets\FBXModel\FBXModel.h"
#include <glm\glm.hpp>
#include <glm\ext.hpp>

Tree::Tree()
{
	
	m_model = new FBXModel("./data/models/tree/treeplan1.fbx");
	m_worldtransform = glm::scale(glm::vec3(0.1, 0.1, 0.1)); // scale
	m_worldtransform = glm::rotate(m_worldtransform, glm::pi<float>() / 2, glm::vec3(0, 1, 0));//Rotate


}

Tree::~Tree()
{

}

void Tree::Draw(unsigned int a_program, Renderer* a_render, glm::vec3 &a_light, FlyCamera &_gameCamera)
{
	m_model->FBXDraw(a_program,a_render,a_light,_gameCamera);
}

void Tree::SetPosition(glm::vec3& a_position)
{
	m_worldtransform[3] = glm::vec4(a_position, 1);
}

