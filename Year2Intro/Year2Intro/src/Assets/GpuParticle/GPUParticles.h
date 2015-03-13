#pragma once

#include "glm\glm.hpp"

struct GPUParticle
{
	GPUParticle() : lifetime(1), lifespan(0){}
	glm::vec3 position;
	glm::vec3 velocity;
	float lifetime;
	float lifespan;
};

