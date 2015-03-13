#pragma once

class FBXFile;
#include "Assets\Camera\FlyCamera.h"
class ParticleEmittor;
class Renderer
{
public:
	Renderer();
	~Renderer();
	//Shader Code

	void CreateOpenGLBuffers(FBXFile* fbx);
	void CleanupOpenGlBuffers(FBXFile* fbx);

	void Generate2DObject();

	GLuint LoadShaderFromFile(std::string a_path, GLenum  a_shadertype);
	//Creates the program,Give it a place to store the program
	bool LoadProgram(std::string a_vertShader, std::string a_fragShader,unsigned int &a_program);
	////Loads the shader into the renderer also runs LoadProgram
	//void LoadShader(std::string a_vertShader, std::string a_fragShader);

	void LoadFBX(const char* string);

	void Draw(FlyCamera &_gameCamera, float a_deltatime);

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

	void TempDraw();
	//Buffer data
	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;

	unsigned int ReturnProgram();
	unsigned int ReturnProgramParticle();
	unsigned int ReturnProgramObject();
	unsigned int ReturnProgramFbx();
protected:

	unsigned int m_ProgramID;
	unsigned int m_ProgramParticle;
	unsigned int m_ProgramObject;
	unsigned int m_ProgramFbx;

	ParticleEmittor* m_cpuEmittor;

	FlyCamera m_gameCamera;

	FBXFile* m_fbx;
};

