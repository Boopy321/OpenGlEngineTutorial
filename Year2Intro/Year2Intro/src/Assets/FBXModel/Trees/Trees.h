#pragma once

#include <glm\glm.hpp>

class FBXModel;
class FlyCamera;
class Renderer;

class Tree
{
public:
	Tree();
	~Tree();

	void Draw(unsigned int a_program, Renderer* a_render, glm::vec3 &a_light, FlyCamera &_gameCamera);

	void SetPosition(glm::vec3& a_position);

	inline void SetModel(FBXModel* a_model){ m_model = a_model; };

	
private:

	FBXModel* m_model;

	glm::mat4 m_worldtransform;
};


