#version 410

in vec3 vNormal;
in vec2 vTexCoord;
in vec4 vPosition;
in vec3 vProjectCam;
in vec3 vColour;

uniform vec3 LightDir;
uniform vec3 LightColour;
uniform vec3 CameraPos;
uniform sampler2D rock_texture;
uniform float SpecPow;
uniform vec3 AmbientIntestity;
uniform vec4 vDiffuse;
out vec4 FragColor;

void main() {
  vec3 ambient = LightColour * AmbientIntestity;
	float d = max(0,
	dot(normalize(vNormal.xyz),LightDir ) );
	vec3 E = normalize( CameraPos - vPosition.xyz );
	vec3 R = reflect( -LightDir, vNormal.xyz );
	float s = max( 0, dot( E, R ) );
	s = pow( s, SpecPow );
	FragColor = texture(rock_texture,vTexCoord) * (vDiffuse *vec4( LightColour * d +
	LightColour * ambient, 1));
 };
