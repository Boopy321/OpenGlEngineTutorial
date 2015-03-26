#version 410

in vec4 vNormal;

out vec4 FragColor;

uniform vec3 LightDir;

void main() {
float d = max(0,dot( normalize(vNormal.xyz),LightDir));
FragColor = vec4(d,d,d,1);
}
