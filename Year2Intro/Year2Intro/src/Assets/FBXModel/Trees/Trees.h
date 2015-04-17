#pragma once

#include <glm\glm.hpp>

class FBXModel;
class FlyCamera;
class Renderer;
class Light;

class Tree
{
public:
	Tree();
	~Tree();

	void Draw(unsigned int a_program, Renderer* a_render,Light* a_light, FlyCamera &_gameCamera);
	void SetPosition(glm::vec3& a_position);

	void SetModel(FBXModel* a_model);
	void SetScale(glm::vec3 a_scale);
private:
	FBXModel* m_model;
	glm::mat4 m_worldtransform;
};


