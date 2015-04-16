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

uniform vec3 iA; //Intensity AMBIENT
uniform vec3 iD; //Intensity Diffuse
uniform vec3 iS; //Intensity Specular Colour
uniform float iSpecPower; //Intensity Power

uniform vec4 vDiffuse; //Mesh Diffuse color
uniform vec3 ProjectionView; //Camera View
uniform vec3 L; //normalised Light Dir

out vec4 FragColor;

void main()
{
	vec3 Ambient = tA * iA;

	float Ndl = max(0.0f,dot(N,-L));
	vec3 Diffuse = tD * iS * Ndl;

	vec3 R = reflect(L,N);
	vec3 E = normalize(ProjectionView - vPosition);

	float specTerm = pow(min(0.0f,dot(R,E)),iSpecPower);
	vec3 Specular = (tS * iS)* specTerm;

	FragColor = vDiffuse * vec4(Ambient + Diffuse + Specular, 1);
};
