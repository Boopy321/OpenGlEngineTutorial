#include "gl_core_4_4.h"
#include "GLFW\glfw3.h"
#include <glm/ext.hpp>
#include <glm/glm.hpp>
#include <stb_image.h>

#include "Assets/Camera/FlyCamera.h"
#include "Gizmos.h"
#include "Application.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "Loaders/ObjLoader/ObjectLoader.h"
#include "Tutorial4.h"

using namespace std;


Tutorial4::Tutorial4(Renderer* a_render)
{
	m_render = a_render;
}

Tutorial4::~Tutorial4()
{

}

void Tutorial4::ImageLoad()
{
	m_render->Generate2DObject();
	//DiffuseMapLoad();
	//NormalMapLoad();

}


void Tutorial4::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	Gizmos::addTransform(glm::mat4(1), 5.0f);

	int loc;
	//Actual Drawing
	glUseProgram(m_program);

	loc = glGetUniformLocation(m_program, "ProjectionView");
	glUniformMatrix4fv(loc, 1, GL_FALSE, &_gameCamera.getProjectionView()[0][0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_normalmap);


	loc = glGetUniformLocation(m_program, "diffuse");
	glUniform1i(loc, 0);

	loc = glGetUniformLocation(m_program, "normal");
	glUniform1i(loc, 1);




	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Tutorial4::GameLoop()
{

}

//void Tutorial4::ShaderProgram()
//{
//	const char* vsSource =  "#version 410\n \
//							 layout(location = 0) in vec4 Position;\
//							 layout(location = 1) in vec4 Tangent; \
//							 layout(location = 2) in vec3 Normal; \
//							 layout(location = 3) in vec2 TexCoord; \
//							 out vec2 vTexCoord; \
//							 out vec3 vNormal; \
//							 out vec3 vTangent; \
//							 out vec3 vBiTangent; \
//							 uniform mat4 ProjectionView; \
//							 void main() { vTexCoord = TexCoord; \
//							 vNormal = Normal.xyz; \
//							 vTangent = Tangent.xyz; \
//							 vBiTangent = cross(vNormal, vTangent); \
//							 gl_Position = ProjectionView * Position; }";
//
//	const char* fsSource =  "#version 410\n \
							in vec2 vTexCoord; \
							in vec3 vNormal; \
							in vec3 vTangent; \
							in vec3 vBiTangent; \
							out vec4 FragColor; \
							uniform vec3 LightDir; \
							uniform sampler2D diffuse; \
							uniform sampler2D normal; \
							void main() { \
							mat3 TBN = mat3( \
							normalize( vTangent ), \
							normalize( vBiTangent ), \
							normalize( vNormal )); \
							vec3 N = texture(normal, \
							vTexCoord).xyz * 2 - 1; \
							float d = max( 0, dot( \
							normalize( TBN * N ), \
							normalize( LightDir ))); \
							FragColor = texture(diffuse, vTexCoord); \
							FragColor.rgb = FragColor.rgb * d;}";

//	int success = GL_FALSE;
//	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//
//	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
//	glCompileShader(vertexShader);
//	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
//	glCompileShader(fragmentShader);
//
//	m_program = glCreateProgram();
//	glAttachShader(m_program, vertexShader);
//	glAttachShader(m_program, fragmentShader);
//	glLinkProgram(m_program);
//
//	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
//
//	if (success == GL_FALSE) {
//		int infoLogLength = 0;
//		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);
//		char* infoLog = new char[infoLogLength];
//
//		glGetProgramInfoLog(m_program, infoLogLength, 0, infoLog);
//		printf("Error:Failed to link Shader program!\n");
//		printf("%s\n", infoLog);
//		delete[] infoLog;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//}
