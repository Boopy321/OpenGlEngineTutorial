#version 410

in vec4 vNormal;
in vec2 frag_texcoord;
out vec4 FragColor;

uniform vec3 LightDir;
uniform sampler2D diffuseTex;

void main() {

FragColor = texture(diffuseTex,frag_texcoord) * vec4(LightDir,1);
}
