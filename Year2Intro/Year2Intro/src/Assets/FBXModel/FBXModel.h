#pragma once

#include <FBXFile.h>

class FBXModel
{
public:
	FBXModel(const char* string);
	~FBXModel();

	void CreateOpenGLBuffers();
	void FBXDraw();

		
	void CleanupOpenGlBuffers();
	void LoadFBX(const char* string);
private:

	FBXFile* m_fbx;


};

