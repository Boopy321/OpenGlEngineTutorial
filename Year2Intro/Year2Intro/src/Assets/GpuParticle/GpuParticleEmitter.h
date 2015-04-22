#pragma once

class GPUParticle;
class Renderer;
#include <glm\glm.hpp>

class GPUParticleEmitter
{
public:
	GPUParticleEmitter(Renderer* a_render);
	virtual ~GPUParticleEmitter();
	//Start up the engine
	void initalise(unsigned int a_maxParticles,
		float a_lifespanMin, float a_lifespanMax,
		float a_velocityMin, float a_velocityMax,
		float a_startSize, float a_endSize,
		const glm::vec4& a_startColour,
		const glm::vec4& a_endColour,
		glm::vec3 a_position);

	//Draw the Beautiful Particles
	void draw(float parTime, float time, const glm::mat4& a_cameraTransform,
		const glm::mat4& a_projectionView);

private: 

	void createBuffers();
	void createUpdateShader();
	void createDrawShader();
	GPUParticle* m_particles;
	unsigned int m_maxParticles;
	glm::vec3 m_position;

	float m_lifespanMin;
	float m_lifespanMax;
	float m_velocityMin;
	float m_velocityMax;
	float m_startSize;
	float m_endSize;

	glm::vec4 m_startColour;
	glm::vec4 m_endColour;

	unsigned int m_activeBuffer;
	unsigned int m_vao[2];
	unsigned int m_vbo[2];
	unsigned int m_drawShader;
	unsigned int m_updateShader;
	float m_lastDrawTime;

	Renderer* m_render;
};

