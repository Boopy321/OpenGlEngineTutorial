#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "FBXModel.h"
#include <FBXFile.h>
#include <iostream>
#include <stb_image.h>

using namespace std;
using glm::vec4;
using glm::vec3;

FBXModel::FBXModel(const char* path,const char* diffuse)
{
	
	LoadFBX(path);
	CreateOpenGLBuffers();
	DiffuseMapLoad(diffuse);
}


FBXModel::~FBXModel()
{
	CleanupOpenGlBuffers();
}


void FBXModel::FBXDraw(unsigned int a_program)
{
	
	int loc = glGetUniformLocation(a_program, "diffuseTex");
	glUniform1i(loc, 1);

	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);
		unsigned int* glData = (unsigned int*)mesh->m_userData;
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_diffuse);

		glBindVertexArray(glData[0]);
		glDrawElements(GL_TRIANGLES,
			(unsigned int)mesh->m_indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void FBXModel::CreateOpenGLBuffers()
{
	//Checks if there is a mesh
	assert(m_fbx->getMeshCount() > 0);

	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);
		// storage for the opengl data in 3 unsigned int
		unsigned int* glData = new unsigned int[3];
		glGenVertexArrays(1, &glData[0]);
		glBindVertexArray(glData[0]);

		glGenBuffers(1, &glData[1]);
		glGenBuffers(1, &glData[2]);

		glBindBuffer(GL_ARRAY_BUFFER, glData[1]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glData[2]);

		glBufferData(GL_ARRAY_BUFFER,
			mesh->m_vertices.size() * sizeof(FBXVertex),
			mesh->m_vertices.data(), GL_STATIC_DRAW);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			mesh->m_indices.size() * sizeof(unsigned int),
			mesh->m_indices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0); // position
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
			sizeof(FBXVertex), 0);

		glEnableVertexAttribArray(1); // normal
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE,
			sizeof(FBXVertex),
			((char*)0) + FBXVertex::NormalOffset);

		glEnableVertexAttribArray(2); // TexCoord
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
			sizeof(FBXVertex),
			((char*)0) + FBXVertex::TexCoord1Offset);


		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		mesh->m_userData = glData;
	}

}
//Cleans up the fbx file
void FBXModel::CleanupOpenGlBuffers()
{
	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i)
	{

		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);

		unsigned int* glData = (unsigned int*)mesh->m_userData;

		glDeleteVertexArrays(1, &glData[0]);
		glDeleteBuffers(1, &glData[1]);
		glDeleteBuffers(1, &glData[2]);
	}
}


void FBXModel::LoadFBX(const char* string)
{
	m_fbx = new FBXFile();
	if (m_fbx->load(string))
	{
		CreateOpenGLBuffers();
		
	}
	else
	{
		cerr << "FBX load Fail" << endl;
	}

	
}

void FBXModel::DiffuseMapLoad(const char* string)
{
	int imageWidth = 0, imageHeight = 0, imageFormat = 0;
	unsigned char* data;

	//load Diffuse map
	data = stbi_load(string,
		&imageWidth, &imageHeight, &imageFormat, STBI_default);

	glGenTextures(1, &m_diffuse);
	glBindTexture(GL_TEXTURE_2D, m_diffuse);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}


