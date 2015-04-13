#version 410

layout(location=0) in vec4 position;
layout(location=1) in vec3 Normal;
layout(location=2) in vec2 texcoord;


uniform mat4 ProjectionView;
out vec2 frag_texcoord;

uniform sampler2D perlin_texture;

void main()
{
	vec4 pos = position;
	pos.y += texture(perlin_texture,texcoord).r * 5;

	frag_texcoord = texcoord;
	gl_Position = ProjectionView * pos;

}