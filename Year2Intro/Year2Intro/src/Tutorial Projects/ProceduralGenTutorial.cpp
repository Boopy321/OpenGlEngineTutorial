#include <gl_core_4_4.h>
#include "ProceduralGenTutorial.h"
#include <glm\glm.hpp>
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "ShadowsTutorial.h"
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

using glm::vec2;

struct gridVerts
{
	glm::vec4 Position;
	glm::vec2 UV;
};

ProceduralGenTutorial::ProceduralGenTutorial(Renderer* a_render)
: m_crate("./data/crate.png")
{
	m_render = a_render;
	m_grid = 100;
	CreatePlane();
}


ProceduralGenTutorial::~ProceduralGenTutorial()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
	glDeleteVertexArrays(1, &m_vao);
}

void ProceduralGenTutorial::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);

	unsigned int m_program = m_render->ReturnProgramParticle();

	m_crate.Bind(0);
	
	glUseProgram(m_program);

	int loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);

	loc = glGetUniformLocation(m_program, "perlin_texture");
	glUniform1i(loc, 0);

	glBindVertexArray(m_vao);
	unsigned int indexCount = (m_grid - 1) * (m_grid - 1) * 6;

	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void ProceduralGenTutorial::GameLoop()
{
}

void ProceduralGenTutorial::CreatePlane()
{
	
	m_verts.resize(m_grid * m_grid);
	int realSize = m_grid * m_grid;

	int count = 0;

	unsigned int* indexData = new unsigned int[(m_grid - 1) *
		(m_grid - 1) * 6];

	//rows
	for (int rows = 0; rows < m_grid; rows++)
	{
		//cols
		for (int cols = 0; cols < m_grid; cols++)
		{
			m_verts[rows * m_grid + cols].Position = glm::vec4((float)cols, 0, (float)rows, 1);
			m_verts[rows * m_grid + cols].UV = glm::vec2((float)cols * 0.01f, (float)rows * 0.01f);

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
			indexData[index++] = currVert;
			indexData[index++] = currVert + m_grid;
			indexData[index++] = currVert + m_grid + 1;

			//Triangle 2
			indexData[index++] = currVert;
			indexData[index++] = currVert + m_grid + 1;
			indexData[index++] = currVert + 1;
		}
	}

	//Places the data into the buffers
	CreateOpenGlBuffers(m_verts, indexData);
}

void ProceduralGenTutorial::CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(gridVerts) * a_pVertex.size(), //Array vector size. Shit ,
		a_pVertex.data(), GL_STATIC_DRAW);


	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(gridVerts), 0);
	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(gridVerts),
		(void*)(sizeof(glm::vec4)));
	//Indics
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo	);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * (m_grid - 1) *
		(m_grid - 1) * 6,
		a_indexData, GL_STATIC_DRAW);
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ProceduralGenTutorial::GenPerlinValues()
{

	int dims = 64;
	float *perlin_data = new float[m_grid * m_grid];
	float scale = (1.0f / dims) * 3;
	
	for (int x = 0; x < m_grid; ++x)
	{
		for (int y = 0; y < m_grid; ++y)
		{
			perlin_data[y * dims + x] = glm::perlin(vec2(x, y) * scale) * 0.5f + 0.5f;
		}
	}

	glGenTextures(1, &m_perlin_texture);
	glBindTexture(GL_TEXTURE_2D, m_perlin_texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, m_grid, m_grid, 0, GL_RED, GL_FLOAT, perlin_data);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}