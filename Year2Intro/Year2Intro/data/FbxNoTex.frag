#version 410

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 LightDir;
uniform vec4 Diffuse;

void main() 
{
	float diffuseLighting = dot(-LightDir, normalize(vNormal));
		
	FragColor = Diffuse * diffuseLighting;
};

