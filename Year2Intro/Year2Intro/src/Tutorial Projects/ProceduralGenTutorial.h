#pragma once

class gridVerts;
class Renderer;
class FlyCamera;
#include <vector>
#include <Assets\Texture2D\Texture2D.h>


class ProceduralGenTutorial
{
public:
	ProceduralGenTutorial(Renderer* a_render);
	~ProceduralGenTutorial();

	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();
	void CreatePlane();
	void GenPerlinValues();
	void CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData);

private:
	unsigned int m_grid;
	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int* indexData;
	unsigned int m_perlin_texture;
	Renderer* m_render;
	std::vector<gridVerts> m_verts;
	Texture2D m_crate;
};

