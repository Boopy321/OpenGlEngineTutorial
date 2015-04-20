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
	//Bunch of stuff for Lighting
	tA = glm::vec3(1, 0, 0);
	tD = glm::vec3(1, 0, 0);
	tS = glm::vec3(1, 0, 0);

	iA = glm::vec3(0.25f, 0.25f, 0.25f);
	iD = glm::vec3(1, 1, 1);
	iS = glm::vec3(1, 1, 1);
}


FBXModel::~FBXModel()
{
	CleanupOpenGlBuffers();
}


void FBXModel::FBXDraw(unsigned int a_program, Renderer* a_render, Light* a_light, FlyCamera &_gameCamera,glm::mat4 &location)
{
	int loc = 0;
	glEnable(GL_BLEND);

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
			
			glm::vec4 takethis = glm::vec4(1);
			loc = glGetUniformLocation(a_program, "vDiffuse");
			glUniform4fv(loc, 1, &takethis[0]);

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

		int loc = glGetUniformLocation(a_program, "MVP");
		glUniformMatrix4fv(loc, 1, GL_FALSE, &(_gameCamera.getProjectionView()* location)[0][0]);
		
		loc = glGetUniformLocation(a_program, "LightDir");
		glUniform3fv(loc, 1, &a_light->m_lightDirection[0]);

		glm::vec3 color = glm::vec3(0);
		loc = glGetUniformLocation(a_program, "LightColour");
		glUniform3fv(loc, 1, &material->diffuse[0]);

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
	glDisable(GL_BLEND);
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

void FBXModel::AdjustPosition(FlyCamera &a_camera)
{


}


