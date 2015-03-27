#pragma once

class gridVerts;

class ProceduralGenTutorial
{
public:
	ProceduralGenTutorial();
	~ProceduralGenTutorial();
	void Draw();
	void GameLoop();
	void CreatePlane();
	void CreateOpenGlBuffers(gridVerts* a_pVertex, unsigned int* a_pIndices);
private:
	unsigned int m_vbo, m_ibo, m_vao;

};

