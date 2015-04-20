#pragma once

#include <glm\glm.hpp>

class FBXModel;
class FlyCamera;
class Renderer;
class Light;
class AntTweakBar;

class Tree
{
public:
	Tree(AntTweakBar* a_bar);
	~Tree();

	void Draw(unsigned int a_program, Renderer* a_render,Light* a_light, FlyCamera &_gameCamera);
	void SetPosition(glm::vec3& a_position);

	void SetModel(FBXModel* a_model);
	void SetScale(glm::vec3 a_scale);
	void SetTransform(glm::mat4 a_transform);
private:
	FBXModel* m_model;
	glm::mat4 m_worldtransform;

};


