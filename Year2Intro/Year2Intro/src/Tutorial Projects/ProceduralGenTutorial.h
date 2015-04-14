#pragma once

class gridVerts;
class Renderer;
class FlyCamera;
class FBXModel;
class Tree;
class AntTweakBar;
#include <vector>
#include <Assets\Texture2D\Texture2D.h>
#include <glm\glm.hpp>

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
	Tree* m_trees;

	Texture2D m_crate;
	AntTweakBar* m_bar;
	
	//FBXModel m_dragon;
	FBXModel* m_tree;
	//FBXModel m_dragon;
	
	glm::vec3 m_lightDirection;

	unsigned int* m_indexData;
	unsigned int m_perlin_texture;
	
	unsigned int m_treelimit;
	int m_treeCount;

	float m_amplitude;
	float m_persistence;

	
	float m_scalar;
	int m_grid;
	int m_octaves;

	static bool m_renegerate;
	static float m_height;
};
