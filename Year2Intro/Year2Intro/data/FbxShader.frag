#version 410

in vec3 vNormal;
in vec2 vTexCoord;

out vec4 FragColor;

uniform vec3 LightDir;
uniform sampler2D diffuseTex;

void main() 
{
	float diffuseLighting = dot(-LightDir, normalize(vNormal));
		
	FragColor = texture(diffuseTex, vTexCoord) * diffuseLighting;
};

