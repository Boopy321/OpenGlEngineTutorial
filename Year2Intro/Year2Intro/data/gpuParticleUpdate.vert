#version 410

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Velocity;
layout(location = 2) in float Lifetime;
layout(location = 3) in float Lifespan;

out vec3 position;
out vec3 velocity;
out float lifetime;
out float lifespan;

uniform float time;
uniform float deltaTime;
uniform float lifeMin;
uniform float lifeMax;
uniform float parTime;
uniform vec3 emitterPosition;

const float INVERSE_MAX_UINT = 1.0f / 4294967295.0f;
float rand(uint seed, float range) {
	uint i = (seed ^ 12345391u) * 2654435769u;
	i ^= (i << 6u) ^ (i >> 26u);
	i *= 2654435769u;
	i += (i << 5u) ^ (i >> 12);
	return float(range * i) * INVERSE_MAX_UINT;
};

vec3 newVelocity;

void main() {
	int scale = 5;
	uint seed = uint(time * 1000.0) + uint(gl_VertexID);
	float t = Lifetime / Lifespan;
	float randVal = rand(seed++, 2) * sin(time);
	float dif = deltaTime;

	newVelocity.x = randVal * -cos(time * t);
	newVelocity.y = sin(t);
	newVelocity.z = tan(t * dif);

	vec3 target = randVal * Velocity * vec3(sin(time), tan(time), cos(time));
	vec3 dir = normalize(Position - target);
	dir.y *= sin(time);
	newVelocity += dir;


	position = Position + (Velocity) * dif;
	velocity = Velocity ;
	lifetime = Lifetime + dif;
	lifespan = Lifespan;

	// emit a new particle as soon as it dies
	if (lifetime > lifespan)
	{
		//uint seed = uint(time * 1000.0) + uint(gl_VertexID);

		// Emitter position
		velocity.x = 0;
		velocity.y = rand(seed++, 2) -4;
		velocity.z = 0;
		velocity = normalize(velocity);
		position = emitterPosition;
		position.x = (rand(seed++, 200 * scale)-100* scale);
		position.z = rand(seed++, 200 * scale)-100* scale;
		lifetime = 0;
		lifespan = rand(seed++, lifeMax - lifeMin) + lifeMin;
	}

}

//float normLifetime = Lifetime / Lifespan;
	//float multiply = parTime;
	//float a = cos(normLifetime * 1);
	//float b = cos(normLifetime * 80);
	//float c = sin(normLifetime * 1);velocity = newVelocity;
	//float y = sin(normLifetime * 80);
	//position.x = a - (pow(b,3));
	//position.y = c - (pow(y,3));
	//position.z = 0;

	//position.x = cos(a*t) - pow(cos(b*t),3);
	//position.y = sin(a*t) - pow(sin(b*t),3);
	//newVelocity.x = cos(a*t) - pow(cos(b*t),3);

//	velocity.x = rand(seed++, 2) - 1;
//	velocity.y = rand(seed++, 2) - 1;
//	velocity.z = rand(seed++, 2) - 1;
