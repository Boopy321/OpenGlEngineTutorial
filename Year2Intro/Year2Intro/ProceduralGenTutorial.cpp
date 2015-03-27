#include <gl_core_4_4.h>
#include "ProceduralGenTutorial.h"
#include <glm\glm.hpp>
#include "VertexStructure.h"

using glm::vec4;
using glm::vec3;

struct gridVerts
{
	glm::vec4 Position;
	glm::vec2 UV;
};

ProceduralGenTutorial::ProceduralGenTutorial()
{
}


ProceduralGenTutorial::~ProceduralGenTutorial()
{
}

void ProceduralGenTutorial::Draw()
{
}

void ProceduralGenTutorial::GameLoop()
{
}

//junk stuff
void ProceduralGenTutorial::CreatePlane()
{
	const int grid = 100;

	gridVerts* verts = new gridVerts[grid];

	unsigned int* indexData = new unsigned int[grid * 3];
	//rows
	for (float rows = 0; rows < grid; rows++)
	{
		//cols
		for (float cols = 0; cols < grid; cols++)
		{
			verts->Position = glm::vec4(cols, 0, rows, 1);
			verts->UV = glm::vec2(cols, rows);
		}
	}

	//Index Values;
	unsigned int index;
	for (unsigned int row = 0; row < grid; row++)
	{
		for (unsigned int col = 0; col < grid; col++)
		{
			int currVert = row * grid + col;
			//Triangle 
			indexData[index++] = currVert;
			indexData[index++] = currVert + grid;
			indexData[index++] = currVert + grid + 1;

			//Triangle 2
			indexData[index++] = currVert;
			indexData[index++] = currVert + grid + 1;
			indexData[index++] = currVert + 1;
		}
	}


}

void ProceduralGenTutorial::CreateOpenGlBuffers(gridVerts* a_pVertex, unsigned int* a_pIndices,unsigned int a_pgrid)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(gridVerts)* 4,
		a_pVertex, GL_STATIC_DRAW);

	//Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(gridVerts), 0);
	// UV
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(gridVerts),
		(void*)(sizeof(glm::vec4)));

	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo	);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* a_pgrid,
		a_pVertex, GL_STATIC_DRAW);
	

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}