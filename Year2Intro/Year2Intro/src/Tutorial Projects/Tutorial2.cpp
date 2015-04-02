#include "gl_core_4_4.h"
#include "Tutorial2.h"
#include "GLFW\glfw3.h"
#include "Gizmos.h"
#include "Application.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "Assets\Camera\FlyCamera.h"
#include "VertexStructure.h"
#include "Assets\Render\Renderer.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

//struct Vertex{
//	glm::vec4 position;
//	glm::vec4 colour;
//};

Tutorial2::Tutorial2(Renderer* a_render)
{
	m_render = a_render;
	ShaderProgram();
	m_render->Generate2DObject();
}

void Tutorial2::GameLoop()
{
}

void Tutorial2::Draw(FlyCamera &_gameCamera, float a_deltatime)
{
	
	glUseProgram(m_programID);

	unsigned int projectionViewUniform =
	glGetUniformLocation(m_programID, "ProjectionView"); 
	unsigned int time =
		glGetUniformLocation(m_programID, "time");

	unsigned int heightScale =
		glGetUniformLocation(m_programID, "heightScale");

	glUniformMatrix4fv(projectionViewUniform, 1, false,
	glm::value_ptr(_gameCamera.getProjectionView()));

	glUniform1f(time, glfwGetTime());
		glUniform1f(heightScale, 1);
	
	glBindVertexArray(m_VAO);
	unsigned int indexCount = (m_rows - 1 ) * (m_cols - 1) * 6;
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

Tutorial2::~Tutorial2()
{
}


void Tutorial2::ShaderProgram()
{

	const char* vsSource = "#version 410\n\
					layout(location=0) in vec4 Position;\
					layout(location=1) in vec4 Colour;\
					out vec4 vColour;\
					uniform mat4 ProjectionView;\
					uniform float time;\
					uniform float heightScale;\
					void main() \
						{vColour = Colour; \
						vec4 P = Position; \
						P.y += sin(time + Position.x)  * heightScale + sin(time + Position.z)  * heightScale; \
						gl_Position = ProjectionView * P; \
						}";

	const char* fsSource = "#version 410\n\
						   in vec4 vColour; \
						   out vec4 FragColor; \
						   void main() { FragColor = vColour; }";

	int success = GL_FALSE;
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertexShader, 1, (const char**)&vsSource, 0);
	glCompileShader(vertexShader);
	glShaderSource(fragmentShader, 1, (const char**)&fsSource, 0);
	glCompileShader(fragmentShader);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader);
	glAttachShader(m_programID, fragmentShader);
	glLinkProgram(m_programID);

	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);

	if (success == GL_FALSE) {
		int infoLogLength = 0; 
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];

		glGetProgramInfoLog(m_programID, infoLogLength, 0, infoLog);
		printf("Error:Failed to link Shader program!\n");
		printf("%s\n", infoLog);
		delete[] infoLog;
	}

	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	}
