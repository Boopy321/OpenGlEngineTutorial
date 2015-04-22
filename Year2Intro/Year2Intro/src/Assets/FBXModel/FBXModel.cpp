#include "gl_core_4_4.h"
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "FBXModel.h"
#include <FBXFile.h>
#include <iostream>
#include <stb_image.h>
#include "Assets\Camera\FlyCamera.h"
#include "Assets\Render\Renderer.h"
#include "Assets\Light\Light.h"

using namespace std;
using glm::vec4;
using glm::vec3;

FBXModel::FBXModel(const char* path)
{
	LoadFBX(path);
	CreateOpenGLBuffers();
	m_fbx->initialiseOpenGLTextures();
}


FBXModel::~FBXModel()
{
	CleanupOpenGlBuffers();
}


void FBXModel::FBXDraw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera,glm::mat4 &)
{
	int loc = 0;
	

	//Turn off when rendering models
	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i)
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);
		unsigned int* glData = (unsigned int*)mesh->m_userData;
		
		FBXMaterial* material = mesh->m_material;
		
		FBXTexture* diffuse = material->textures[material->DiffuseTexture];
		
		if (diffuse == nullptr)
		{
			a_program = a_render->ReturnProgramFBXnoTex();
			glUseProgram(a_program);
		
			//So the rocks dont look crappy
			glActiveTexture(GL_TEXTURE0);
			
			//Wrapping it hopefully with the Background texture
			loc = glGetUniformLocation(a_program, "rock_texture");
			glUniform1i(loc, 0);

			loc = glGetUniformLocation(a_program, "vDiffuse");
			glUniform4fv(loc, 1, &material->diffuse[0]);

		}
		else
		{//CHANGED
			a_program = a_render->ReturnProgramFBX();
			glUseProgram(a_program);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuse->handle);

			loc = glGetUniformLocation(a_program, "box_texture");
			glUniform1i(loc, 0);
		}

		glm::mat4 gamestuff = _gameCamera.getProjectionView() * m_worldTransform;
		int loc = glGetUniformLocation(a_program, "MVP");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &gamestuff[0][0]);
		
		loc = glGetUniformLocation(a_program, "LightDir");
		glUniform3fv(loc, 1, &a_light->m_lightDirection[0]);

		glm::vec3 color = glm::vec3(1);
		loc = glGetUniformLocation(a_program, "LightColour");
		glUniform3fv(loc, 1, &a_light->m_diffuse[0]);

		loc = glGetUniformLocation(a_program, "CameraPos");
		glUniform3fv(loc, 1, &_gameCamera.GetPosition()[0]);

		loc = glGetUniformLocation(a_program, "AmbientIntestity");
		glUniform3fv(loc, 1, &a_light->m_ambient[0]);

		loc = glGetUniformLocation(a_program, "SpecPow");
		glUniform1f(loc, a_light->m_spec);

		glBindVertexArray(glData[0]);

		glDrawElements(GL_TRIANGLES,
			(unsigned int)mesh->m_indices.size() , GL_UNSIGNED_INT, 0);
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
		glVertexAttribPointer(2, 2,GL_FLOAT, GL_FALSE,
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

void FBXModel::SetTransform(glm::mat4 transform)
{
	 m_worldTransform = transform;
}


