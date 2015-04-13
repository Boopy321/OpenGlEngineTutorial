#pragma once

#include <FBXFile.h>

class FBXModel
{
public:
	FBXModel(const char* path, const char* diffuse);
	FBXModel();
	~FBXModel();

	void CreateOpenGLBuffers();
	void FBXDraw(unsigned int a_program);

	void DiffuseMapLoad(const char* string);
	void CleanupOpenGlBuffers();
	void LoadFBX(const char* string);
private:

	FBXFile* m_fbx;
	unsigned int m_diffuse;
	
};

