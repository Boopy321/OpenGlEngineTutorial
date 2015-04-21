#pragma once

#include <FBXFile.h>
class FlyCamera; 
class Renderer;
class Light;

class FBXModel
{
public:
	FBXModel(const char* path);
	FBXModel();
	~FBXModel();

	void CreateOpenGLBuffers();
	void FBXDraw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera, glm::mat4 &location);

	void SetTransform(glm::mat4 transform);
	void NormalMapLoad(const char* string);
	void DiffuseMapLoad(const char* string);
	void CleanupOpenGlBuffers();
	void LoadFBX(const char* string);
	void AdjustPosition(FlyCamera &a_camera);
private:

	FBXFile* m_fbx;
	unsigned int m_diffuse;
	unsigned int m_normalmap;

	glm::mat4 m_worldTransform;

};

