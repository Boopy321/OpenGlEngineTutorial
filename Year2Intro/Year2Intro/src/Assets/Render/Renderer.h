#pragma once

class FBXFile;
#include "Assets\Camera\FlyCamera.h"
class ParticleEmittor;
class Renderer
{
public:
	Renderer();
	~Renderer();
	
	void Generate2DObject();

	GLuint LoadShaderFromFile(std::string a_path, GLenum  a_shadertype);
	//Creates the program,Give it a place to store the program
	bool LoadProgram(std::string a_vertShader, std::string a_fragShader,unsigned int &a_program);
	////Loads the shader into the renderer also runs LoadProgram
	//void LoadShader(std::string a_vertShader, std::string a_fragShader);

	bool LoadDrawProgram(std::string a_gpuVERT, std::string a_gpuGEOMETRY, std::string a_gpuFRAG, unsigned int &a_gpuprogram);
	void LoadFBX(const char* string);

	void Draw(FlyCamera &_gameCamera, float a_deltatime);

	void DrawQuad();

	void StartCpuParticle(unsigned int a_maxParticles,
		unsigned int a_emitRate,
		float a_lifetimeMin, float a_lifetimeMax,
		float a_velocityMin, float a_velocityMax,
		float a_startSize, float a_endSize,
		const glm::vec4& a_startColour, const glm::vec4& a_endColour);

	unsigned int LoadObject(const char* filepath);

	void GenerateGrid(unsigned int rows, unsigned int cols);

	//Deconstructor stuff
	void Close();
	//Whatever Fbx model is loaded.
	void FBXDraw();
	//Buffer data
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int ReturnProgram();
	unsigned int ReturnProgramParticle();
	unsigned int ReturnProgramObject();
	unsigned int ReturnProgramFbx();
	unsigned int ReturnProgramPostProcess();
	unsigned int ReturnProgramShadow();
	unsigned int ReturnProgramShadowMap();
	unsigned int ReturnProgramFBX();
	unsigned int ReturnProgramMap();
	unsigned int ReturnProgramTerrain();
	unsigned int ReturnProgramFBXnoTex();

	void MapTexture();
	void DrawShadowCast();
	
	void DiffuseMapLoad();
	void NormalMapLoad();

protected:
	//Variables to contain the shader programs
	unsigned int m_GPUProgram;
	unsigned int m_ProgramID;
	unsigned int m_ProgramParticle;
	unsigned int m_ProgramObject;
	unsigned int m_ProgramFbx;
	unsigned int m_ProgramPostProcess;
	unsigned int m_ProgramShadow;
	unsigned int m_ProgramShadowMap;
	unsigned int m_ProgramMapLoad;
	unsigned int m_programTerrain;
	unsigned int m_programFBXnoTex;
	unsigned int m_texture, m_normalmap;

	ParticleEmittor* m_cpuEmittor;

	FlyCamera m_gameCamera;

	FBXFile* m_fbx;
};

