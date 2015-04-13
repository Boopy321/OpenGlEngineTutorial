#pragma once

class gridVerts;
class Renderer;
class FlyCamera;
class AntTweakBar;
#include <vector>
#include <Assets\Texture2D\Texture2D.h>


class ProceduralGenTutorial
{
public:
	ProceduralGenTutorial(Renderer* a_render, AntTweakBar* a_bar);
	~ProceduralGenTutorial();

	void Draw(FlyCamera &_gameCamera, float a_deltatime);
	void GameLoop();
	void CreatePlane();
	void GenerateTerrain();
	void CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData);
	void TweakBarTerrain(AntTweakBar a_bar);
	void GenerateNormal(gridVerts* a_vert1, gridVerts* a_vert2, gridVerts* a_vert3);
	void GeneratePerlin();
	void GenNormalLoop();
	static void GenTerrain();
	void DrawNormals();

private:

	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int* indexData;

	Renderer* m_render;
	std::vector<gridVerts> m_verts;
	Texture2D m_crate;
	AntTweakBar* m_bar;
	static float m_height;
	unsigned int* m_indexData;
	unsigned int m_perlin_texture;
	int m_grid;
	float m_amplitude;
	float m_persistence;
	int m_octaves;
	static bool m_renegerate;

};
