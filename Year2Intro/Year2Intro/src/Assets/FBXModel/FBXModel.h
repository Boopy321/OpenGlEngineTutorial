#pragma once

#include <FBXFile.h>
class FlyCamera; 
class Renderer;
class FBXModel
{
public:
	FBXModel(const char* path);
	FBXModel();
	~FBXModel();

	void CreateOpenGLBuffers();
	void FBXDraw(unsigned int a_program, Renderer* a_render, glm::vec3 &a_light, FlyCamera &_gameCamera, glm::mat4 &location);


	void NormalMapLoad(const char* string);
	void DiffuseMapLoad(const char* string);
	void CleanupOpenGlBuffers();
	void LoadFBX(const char* string);
	void AdjustPosition(FlyCamera &a_camera);
private:

	FBXFile* m_fbx;
	unsigned int m_diffuse;
	unsigned int m_normalmap;

	
	glm::vec3 m_lightAmbient;
	glm::vec3 diffuse;
	float m_spec;

	float m_lightAmbIntensity;
	float m_diffuseIntensity;
	float m_specularIntensity;
	
};

