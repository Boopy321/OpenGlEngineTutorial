#include <gl_core_4_4.h>
#include "ProceduralGenTutorial.h"
#include <glm\glm.hpp>
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Assets\RenderTargets\RenderTarget.h"
#include <glm\glm.hpp>
#include "Assets\Render\Renderer.h"
#include "Gizmos.h"
#include "Assets\Camera\FlyCamera.h"
#include "FBXFile.h"
#include <glm/ext.hpp>
#include <glm\gtc\noise.hpp>
#include "Assets\Texture2D\Texture2D.h"
#include <vector>
#include "Assets\FBXModel\FBXModel.h"
#include "Assets\AntTweakBar\AntTweakBar.h"
#include "Assets\FBXModel\Trees\Trees.h"
#include "Assets\GpuParticle\GpuParticleEmitter.h"
#include "Assets\Light\Light.h"
#include <limits>

using glm::vec2;

float ProceduralGenTutorial::m_height(0.0f);
bool ProceduralGenTutorial::m_renegerate(true);

struct gridVerts
{
	glm::vec4 Position;
	glm::vec3 Normal;
	glm::vec2 UV;
};

ProceduralGenTutorial::ProceduralGenTutorial(Renderer* a_render,AntTweakBar* a_bar,Light* a_light)
: m_crate("./data/crate.png")
{
	m_render = a_render;
	m_grid = 100;
	m_perlin_data = new float[m_grid * m_grid];
	m_amplitude = 6.f;
	m_persistence = 0.3f;
	//m_bar = a_bar;
	m_scalar = 3.0f;
	m_treelimit = 50;
	m_treeCount = 20;
	m_seed = 10000;
	m_light = a_light;
	m_lightdir = m_light->getLightDir();

	//m_tree = new FBXModel("./data/models/cube.fbx");
	
	CreatePlane();
	//TweakBarStuff
	//m_bar->RegenerateTerrain();
//	m_bar->AddFloatToTwBar("Seed", &m_seed);
//	m_bar->AddIntToTwBar("TreeLimit", &m_treeCount);
//	m_bar->AddFloatToTwBar("Amplitude", &m_amplitude);
//	m_bar->AddFloatToTwBar("Persistence", &m_persistence);
//	m_bar->AddBoolToTwBar("Regenerate?", &m_renegerate);
//	m_bar->AddVec3ToTwBar("m_lightDirection", &m_light->m_lightDirection);

	//glGenTextures(1, &m_perlin_texture);

	//m_trees = new Tree[m_treelimit];
	//for (int i = 0; i < m_treeCount; i++)
	//{
	//	m_trees[i].SetModel(m_tree);
	//}
	   //
	float *perlin_data = new float[m_grid * m_grid];
}


ProceduralGenTutorial::~ProceduralGenTutorial()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

void ProceduralGenTutorial::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	int m_program = 0;

	Gizmos::addTransform(glm::mat4(1), 5.0f);
	//DrawNormals();
	//FBX Model stuff
	//for (int i = 0; i < m_tree; i++)
	//{
	//	if ()
	//	{

	//	}
	//	else
	//	{

	//	}
	//}
	//m_trees->Draw(m_program, m_render, m_light, _gameCamera);
//Terrain Code
	m_program = m_render->ReturnProgramTerrain();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_perlin_texture);

	glUseProgram(m_program);

	m_crate.Bind(1);

	int loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);
   
	loc = glGetUniformLocation(m_program, "perlin_texture");
	glUniform1i(loc, 0);
   
	loc = glGetUniformLocation(m_program, "Light");
	glUniform3fv(loc, 1, &m_light->m_lightDirection[0]);
   
	loc = glGetUniformLocation(m_program, "box_texture");
	glUniform1i(loc, 1);
   
	loc = glGetUniformLocation(m_program, "Scale");
	glUniform1f(loc, m_scalar);
	   
	glBindVertexArray(m_vao);
	unsigned int indexCount = ((m_grid - 1) * (m_grid - 1)) * 6;

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void ProceduralGenTutorial::GameLoop()
{
	if (m_renegerate)
	{
		GenerateTerrain();
	}
}

void ProceduralGenTutorial::CreatePlane()
{

	m_indexData = new unsigned int[(m_grid - 1)*(m_grid - 1) * 6];
	m_verts.resize(m_grid * m_grid);
	int realSize = m_grid * m_grid;

	int count = 0;


	//rows
	for (int rows = 0; rows < m_grid; rows++)
	{
		//cols
		for (int cols = 0; cols < m_grid; cols++)
		{
			m_verts[rows * m_grid + cols].Position = glm::vec4((((float)cols - (m_grid / 2)) * m_scalar), 0, (((float)rows - (m_grid / 2))* m_scalar), 1);
			m_verts[rows * m_grid + cols].Normal = glm::vec3(0, 1, 0);
			//Tex Coords
			m_verts[rows * m_grid + cols].UV = glm::vec2(((float)cols / (float)m_grid), ((float)rows / (float)m_grid));
			count++;
		}
	}
	////Index Values
	unsigned int index = 0;
	for (unsigned int row = 0; row < m_grid - 1; row++)
	{
		for (unsigned int col = 0; col < m_grid - 1; col++)
		{
			int currVert = row * m_grid + col;
			//Triangle 
			m_indexData[index++] = currVert;
			m_indexData[index++] = currVert + m_grid;
			m_indexData[index++] = currVert + m_grid + 1;

			//Triangle 2
			m_indexData[index++] = currVert;
			m_indexData[index++] = currVert + m_grid + 1;
			m_indexData[index++] = currVert + 1;
		}
	}

	//Places the data into the buffers
	CreateOpenGlBuffers(m_verts, m_indexData);
}

void ProceduralGenTutorial::CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(gridVerts) * a_pVertex.size(), //Array vector size. Shit ,
		a_pVertex.data(), GL_DYNAMIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(gridVerts), 0);
	//Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(gridVerts), (void*)offsetof(gridVerts, Normal));
	//UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gridVerts), (void*)offsetof(gridVerts, UV));

	//Indics
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo	);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * ((m_grid - 1)*(m_grid - 1) * 6),
		a_indexData, GL_STATIC_DRAW);
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Creates the perlin and Normal Values
void ProceduralGenTutorial::GenerateTerrain()
{
	GeneratePerlin();
	m_renegerate = false;
}

void ProceduralGenTutorial::GeneratePerlin()
{
	int dims = m_grid;
	
	float scale = (1.0f / dims) * 3;
	m_octaves = 6;

	float height = 0;
	float heightmax = 0;
	float heightmin = std::numeric_limits<float>::max();

	for (int x = 0; x < m_grid; ++x)
	{
		for (int y = 0; y < m_grid; ++y)
		{
			float amplitude = m_amplitude;
			float persistence = m_persistence;
			m_perlin_data[y * dims + x] = 0;
			glm::perlin(vec2(x, y) * scale) * 0.5f + 0.5f;

			for (int o = 0; o < m_octaves; ++o)
			{
				float freq = powf(2, (float)o);
				float perlin_sample = glm::perlin(vec3((float)x, (float)y,m_seed)* scale * freq) * 0.5f + 0.5f;

				m_perlin_data[y* dims + x] += perlin_sample * amplitude;
				amplitude *= persistence;

				height = perlin_sample * amplitude;

				if (height < heightmin)
					heightmin = height;
				else if (height >heightmax)
				{
					heightmax = height;
				}
			}

		}
	}

	//Offsets the heights so they arent crazy
	float heightDif = heightmax - heightmin;
	for ( int i = 0; i < m_grid * m_grid; ++i)
	{
		m_perlin_data[i] -= heightDif;
	}
	//Calculate normals here before the shader
	//Throw in the Perlin Data instead of the Grid verts
	//Dont use the texture untill normals are calced
	
	
	for (unsigned int i = 0; i < m_verts.size(); i++)
	{
		m_verts[i].Position.y = m_perlin_data[i] * m_scalar;
	}

	GenNormalLoop();

	glBindBuffer(GL_ARRAY_BUFFER,m_vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_grid * m_grid *
		sizeof(gridVerts), m_verts.data());
}

void ProceduralGenTutorial::GenerateNormal(gridVerts* a_vert1, gridVerts* a_vert2, gridVerts* a_vert3)
{
	// Calculate face normal
	glm::vec3 d1(a_vert3->Position - a_vert1->Position);
	glm::vec3 d2(a_vert2->Position - a_vert1->Position);

	glm::vec3 crossProduct = glm::cross(d1, d2);

	// Normalise normal
	glm::vec3 normal = glm::normalize(crossProduct);

	a_vert1->Normal = normal;
	a_vert2->Normal = normal;
	a_vert3->Normal = normal;
}

void ProceduralGenTutorial::GenNormalLoop()
{
	unsigned int indiciesSize = (m_grid - 1) * (m_grid - 1) * 6;
	for (unsigned int i = 0; i < indiciesSize; i += 3)
	{
		gridVerts* vertex1 = &m_verts[m_indexData[i + 2]];
		gridVerts* vertex2 = &m_verts[m_indexData[i + 1]];
		gridVerts* vertex3 = &m_verts[m_indexData[i]];

		GenerateNormal(vertex1, vertex2, vertex3);
	}
}

void ProceduralGenTutorial::GenTerrain()
{
	m_renegerate = true;
}

void ProceduralGenTutorial::DrawNormals()
{
	glm::vec4 lineColour(1.0f, 0.0f, 0.0f, 1.0f);

	for (unsigned int i = 0; i < m_verts.size(); ++i)
	{
		glm::vec3 vertPos = m_verts[i].Position.xyz;
		glm::vec3 vertNormal = m_verts[i].Normal;

		Gizmos::addLine(vertPos, vertPos + vertNormal, lineColour);
	}
}