#version 410

in vec3 vNormal;
in vec2 vTexCoord;
in vec3 vPosition;
in vec3 vProjectCam;


in vec3 N; //Normalised Surface normal from mesh
in vec3 P; //world-space surface position from mesh

uniform vec3 tA; //AMBIENT //
uniform vec3 tD; //DIFFUSE
uniform vec3 tS; //SPEC

uniform vec3 iA;
uniform vec3 iD;
uniform vec3 iS;
uniform float iSpecPower;

uniform sampler2D diffuseTex;
uniform vec3 ProjectionView;
uniform vec3 L; //normalised Light Dir

out vec4 FragColor;

void main() 
{
	float Ambient = tA * iA;

	float Ndl = max(0.0f,dot(N,-L));
	vec3 Diffuse = tD * iS * Ndl;

	vec3 R = reflect(L,N);
	vec3 E = normalize(ProjectionView - Position);

	float specTerm = pow(min(0.0f,dot(R,E)),ISpecPower);
	vec3 Specular = (tS * iS)* specTerm;

	float diffuseLighting = dot(-LightDir, normalize(vNormal));
		
	FragColor = texture(diffuseTex, vTexCoord) *vec4(Ambient + Diffuse + Specular, 1);
};

