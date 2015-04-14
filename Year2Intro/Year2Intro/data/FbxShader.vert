#version 410

layout(location=0) in vec4 Position;
layout(location=1) in vec4 Normal;
layout(location=2) in vec2 TexCoord;

out vec3 vNormal;
out vec2 vTexCoord;


uniform mat4 MVP;

void main()
{
	vTexCoord = TexCoord;
	vNormal = Normal.xyz;

	gl_Position = MVP*Position;

}
