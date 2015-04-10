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
	static void GenerateTerrain();
	void CreateOpenGlBuffers(std::vector<gridVerts> a_pVertex, unsigned int* a_indexData);
	void TweakBarTerrain(AntTweakBar a_bar);
private:

	unsigned int m_vbo, m_ibo, m_vao;
	unsigned int* indexData;


	Renderer* m_render;
	std::vector<gridVerts> m_verts;
	Texture2D m_crate;
	AntTweakBar* m_bar;
	static float height;
	static unsigned int m_perlin_texture;
	static int m_grid;
	static float m_amplitude;
	static float m_persistence;
	static int m_octaves;

};
