#include "gl_core_4_4.h"
#include "Renderer.h"
#include "GLFW\glfw3.h"
#include <string>
#include <FBXFile.h>
#include <stb_image.h>
#include <glm\glm.hpp>
#include <glm/ext.hpp>
#include "VertexStructure.h"
#include "Loaders\ObjLoader\ObjectLoader.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include "Assets\CpuParticle\ParticleEmittor.h"

using namespace std;
using glm::vec4;
using glm::vec3;

Renderer::Renderer()
{
	//start up all of the programs here
	LoadProgram("./data/Tute3VertShader.glvs","./data/Tute3FragShader.glfs",m_ProgramObject);
	LoadProgram("./data/Terrain.vert","./data/Terrain.frag",m_ProgramParticle);
	LoadProgram("./data/RenderShader.vert", "./data/RenderShader.frag", m_ProgramID);
	LoadProgram("./data/PostProcess.vertex", "./data/PostProcess.Frag", m_ProgramPostProcess);
	LoadProgram("./data/Shadows.vert", "./data/Shadows.Frag", m_ProgramShadow);
	LoadProgram("./data/FbxShader.vert", "./data/FbxShader.Frag", m_ProgramFbx);
	LoadProgram("./data/ShadowMap.vert", "./data/ShadowMap.Frag", m_ProgramShadowMap);
	LoadProgram("./data/DifNormMapLoader.vert", "./data/DifNormMapLoader.frag", m_ProgramMapLoad);
	LoadProgram("./data/Terrain.vert", "./data/Terrain.frag", m_programTerrain);
	LoadProgram("./data/Fbxshader.vert", "./data/FbxNoTex.frag", m_programFBXnoTex);
}

Renderer::~Renderer()
{
	

}

void Renderer::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	
}

GLuint Renderer::LoadShaderFromFile(std::string a_path, GLenum  a_shadertype)
{
	{
		//Open file
		GLuint shaderID = 0;
		std::string shaderString;
		std::ifstream sourceFile(a_path.c_str());

		//Source file loaded
		if (sourceFile)
		{
			//Get shader source
			shaderString.assign((std::istreambuf_iterator< char >(sourceFile)), std::istreambuf_iterator< char >());
			//Create shader ID
			shaderID = glCreateShader(a_shadertype);

			//Set shader source
			const GLchar* shaderSource = shaderString.c_str();
			glShaderSource(shaderID, 1, (const GLchar**)&shaderSource, NULL);

			//Compile shader source
			glCompileShader(shaderID);

			//Check shader for errors
			GLint shaderCompiled = GL_FALSE;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &shaderCompiled);
			if (shaderCompiled != GL_TRUE)
			{
				int bufflen;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &bufflen);
				char* log = new char[bufflen + 1];

				glGetShaderInfoLog(shaderID, bufflen, 0, log);


				printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderID, log);

				delete log;
				glDeleteShader(shaderID);
				shaderID = 0;
			}
		}
		else
		{
			printf("Unable to open file %s\n", a_path.c_str());
		}

		return shaderID;
	}
}


bool Renderer::LoadProgram(std::string a_vertShader, std::string a_fragShader, unsigned int &a_program)
{
	//Generate program
	unsigned int ProgramID = glCreateProgram();
	//Load vertex shader
	GLuint vertexShader = LoadShaderFromFile(a_vertShader, GL_VERTEX_SHADER);

	//Check for errors
	if (vertexShader == 0)
	{
		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;
	}

	//Attach vertex shader to program
	glAttachShader(ProgramID, vertexShader);

	GLuint fragmentShader = LoadShaderFromFile(a_fragShader, GL_FRAGMENT_SHADER);

	//Check for errors
	if (fragmentShader == 0)
	{
		glDeleteShader(vertexShader);
		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;
	}
	//Attach fragment shader to program
	glAttachShader(ProgramID, fragmentShader);

	//Link program
	glLinkProgram(ProgramID);

	//Check for errors
	GLint programSuccess = GL_TRUE;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &programSuccess);
	if (programSuccess != GL_TRUE)
	{
		printf("Error linking program %d!\n", m_ProgramID);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(ProgramID);
		ProgramID = 0;
		return false;
	}

	//Clean up excess shader references
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	a_program = ProgramID;
	return true;

}
//Returns the index data requried for the model
unsigned int Renderer::LoadObject(const char* filepath)
{

	std::vector< Vertex > verts;
	ObjectLoader* objLoader = new ObjectLoader(filepath, verts);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* verts.size(), &verts[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	//Position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//Colour
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colour) );// (void*)(sizeof(vec4)* 2 + sizeof(vec3)+sizeof(glm::vec2)));
	//Normals
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal) );

	int indexData = objLoader->getModel()->vIndices.size();

	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData * sizeof(GLuint), &objLoader->getModel()->vIndices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	delete objLoader;

	return indexData;
}

//Predefined vertex Data. Allows Creation of a 2D Object
void Renderer::Generate2DObject()
{
	Vertex vertexData[] =
	{
		{ vec4(-50, 0, 50, 1), vec4(0, 1, 0, 0), vec3(1, 0, 0), glm::vec2(0, 1) },
		{ vec4(50, 0, 50, 1), vec4(0, 1, 0, 0), vec3(1, 0, 0), glm::vec2(1, 1) },
		{ vec4(50, 0, -50, 1), vec4(0, 1, 0, 0), vec3(1, 0, 0), glm::vec2(1, 0) },
		{ vec4(-50, 0, -50, 1), vec4(0, 1, 0, 0), vec3(1, 0, 0), glm::vec2(0, 0) },
	};

	unsigned int indexData[] = { 0, 1, 2, 0, 2, 3 };

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 4,
		vertexData, GL_STATIC_DRAW);


	glGenBuffers(1, &m_IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* 6,
		indexData, GL_STATIC_DRAW);
	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);
	//Tangent
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)(sizeof(vec4)));
	//Normal
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), (void*)(sizeof(vec4)* 2));
	//Texture 
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), ((void*)(sizeof(vec4)* 2 + (sizeof(vec3)))));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


////MUST USE if you want to draw, Requires external shaders
//void Renderer::LoadShader(std::string a_vertShader, std::string a_fragShader)
//{
//	LoadProgram(a_vertShader, a_fragShader);
//}




//Starts up the particle emittor based of the data given
//returns the emittor so draw and update can be controlled.
void Renderer::StartCpuParticle(unsigned int a_maxParticles,
	unsigned int a_emitRate,
	float a_lifetimeMin, float a_lifetimeMax,
	float a_velocityMin, float a_velocityMax,
	float a_startSize, float a_endSize,
	const glm::vec4& a_startColour, const glm::vec4& a_endColour)
{
	m_cpuEmittor = new ParticleEmittor();
	m_cpuEmittor->initalise(a_maxParticles,
		a_emitRate,
		a_lifetimeMin, a_lifetimeMax,
		a_velocityMin, a_velocityMax,
		a_startSize, a_endSize,
		a_startColour, a_endColour);

}

void Renderer::GenerateGrid(unsigned int rows, unsigned int cols)
{
	int m_rows = rows;
	int m_cols = cols;

	Vertex* aoVertices = new Vertex[rows * cols];
	for (unsigned int r = 0; r < rows; ++r)
	{
		for (unsigned int c = 0; c < cols; ++c)
		{
			aoVertices[r * cols + c].position = vec4((float)c, 0
				, (float)r, 1);
			//Time to create a crazy color for thet texture
			//Totally wont be related what so ever
			vec3 colour = vec3(sinf((c / (float)(cols - 1))*
				(r / (float)(rows - 1))));
			aoVertices[r * cols + c].colour = glm::vec4(colour, 1);
		}

	}

	unsigned int* auiIndices = new unsigned int[(rows - 1) * (cols - 1) * 6];
	unsigned int index = 0;

	for (unsigned int r = 0; r < (rows - 1); ++r)
	{
		for (unsigned int c = 0; c < (cols - 1); ++c)
		{
			//Triangle 1
			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);

			auiIndices[index++] = r * cols + c;
			auiIndices[index++] = (r + 1) * cols + (c + 1);
			auiIndices[index++] = r * cols + (c + 1);
		}
	}

	//To be continued :)
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_IBO);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, (rows * cols) * sizeof(Vertex),
		aoVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex,colour));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (rows)* (cols)* 6 *
		sizeof(unsigned int), auiIndices, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	
	delete[] aoVertices;
	delete[] auiIndices;

}

unsigned int Renderer::ReturnProgram()
{
	return m_ProgramID;
}

unsigned int Renderer::ReturnProgramParticle()
{
	return m_ProgramParticle;
}

unsigned int Renderer::ReturnProgramObject()
{
	return m_ProgramObject;
}

unsigned int Renderer::ReturnProgramPostProcess()
{
	return m_ProgramPostProcess;
}

unsigned int Renderer::ReturnProgramShadow()
{
	return m_ProgramShadow;
}

unsigned int Renderer::ReturnProgramShadowMap()
{
	return m_ProgramShadowMap;
}

unsigned int Renderer::ReturnProgramFBX()
{
	return m_ProgramFbx;
}


unsigned int Renderer::ReturnProgramMap()
{
	return m_ProgramMapLoad;
}

unsigned int Renderer::ReturnProgramTerrain()
{
	return m_programTerrain;
}

unsigned int Renderer::ReturnProgramFBXnoTex()
{
	return m_programFBXnoTex;
}

void Renderer::Close()
{
	
	glDeleteProgram(m_ProgramID);
	glDeleteProgram(m_ProgramParticle);
	glDeleteProgram(m_ProgramObject);
	glDeleteProgram(m_ProgramFbx);


}

void Renderer::DrawShadowCast()
{
	for (unsigned int i = 0; i < m_fbx->getMeshCount(); ++i) 
	{
		FBXMeshNode* mesh = m_fbx->getMeshByIndex(i);
		unsigned int* glData = (unsigned int*)mesh->m_userData;
		glBindVertexArray(glData[0]);
		glDrawElements(GL_TRIANGLES,
			(unsigned int)mesh->m_indices.size(),
			GL_UNSIGNED_INT, 0);
	}

}

void Renderer::DrawQuad()
{

}


void Renderer::NormalMapLoad()
{
	//load Normal Map
	int imageWidth = 0, imageHeight = 0, imageFormat = 0;
	unsigned char* data;

	data = stbi_load("./data/model/¢ú-ÚÁ+¦÷/001/00002671/Texture2D/Normal.tga",
		&imageWidth, &imageHeight, &imageFormat, STBI_default);
	
	glGenTextures(1, &m_normalmap);
	glBindTexture(GL_TEXTURE_2D, m_normalmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	stbi_image_free(data);
}

void Renderer::MapTexture()
{
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_normalmap);
}