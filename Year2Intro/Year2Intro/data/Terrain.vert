#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 texcoord;


uniform mat4 ProjectionView;
out vec2 frag_texcoord;
out vec3 vNormal;
out vec3 vPosition;

void main()
{
	frag_texcoord = texcoord;
	gl_Position = ProjectionView * position;
	vNormal = Normal;
	vPosition = position.xyz;
}
