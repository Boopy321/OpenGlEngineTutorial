//#include "gl_core_4_4.h"
//#include "GLFW\glfw3.h"
//#include "TinyObjSideProject.h"
//#include <glm/ext.hpp>
//#include <glm/glm.hpp>
//#include <stb_image.h>
//#include "FlyCamera.h"
//#include "Gizmos.h"
//#include "Application.h"
//#include <iostream>
//#include <cstdlib>
//#include <stdlib.h>
//#include <time.h>
//#include "ObjectLoader.h"
//#include <AntTweakBar.h>
//#include "tiny_obj_loader.h"
//
//using namespace std;
//
////
//
//TinyObjSideProject::TinyObjSideProject()
//{
//}
//
//TinyObjSideProject::~TinyObjSideProject()
//{
//}
//
//void TinyObjSideProject::CreateOpenGlBuffers(std::vector<tinyobj::shape_t>& shapes)
//{
//
//	m_gl_info.resize(shapes.size());
//
//	for (unsigned int mesh_index = 0; mesh_index < shapes.size(); ++mesh_index)	
//	{
//		glGenVertexArrays(1, &m_gl_info[mesh_index].m_VAO);
//		glGenBuffers(1, &m_gl_info[mesh_index].m_VBO);
//
//		glGenBuffers(1, &m_gl_info[mesh_index].m_IBO);
//		glBindVertexArray(m_gl_info[mesh_index].m_VAO);
//
//		unsigned int float_count = shapes[mesh_index].mesh.positions.size();
//		float_count += shapes[mesh_index].mesh.normals.size();
//		float_count += shapes[mesh_index].mesh.texcoords.size();
//
//		std::vector<float> vertex_data;
//		vertex_data.reserve(float_count);
//
//		vertex_data.insert(vertex_data.end(),
//			shapes[mesh_index].mesh.positions.begin(),
//			shapes[mesh_index].mesh.positions.end());
//
//		vertex_data.insert(vertex_data.end(),
//			shapes[mesh_index].mesh.normals.begin(),
//			shapes[mesh_index].mesh.normals.end());
//
//		m_gl_info[mesh_index].m_index_count =
//			shapes[mesh_index].mesh.indices.size();
//
//		glBindBuffer(GL_ARRAY_BUFFER, m_gl_info[mesh_index].m_VBO);
//		glBufferData(GL_ARRAY_BUFFER,
//			vertex_data.size() * sizeof(float),
//			vertex_data.data(), GL_STATIC_DRAW);
//
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_info[mesh_index].m_IBO);
//
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
//			shapes[mesh_index].mesh.indices.size() * sizeof(unsigned int),
//			shapes[mesh_index].mesh.indices.data(), GL_STATIC_DRAW);
//
//		glEnableVertexAttribArray(0); //position
//		glEnableVertexAttribArray(1); //normal data
//
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0,
//			(void*)(sizeof(float)*shapes[mesh_index].mesh.positions.size()));
//		glBindVertexArray(0);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	}
//
//}
//
//void TinyObjSideProject::ImageLoad()
//{
//	
//}
//
//void TinyObjSideProject::Draw(FlyCamera &_gameCamera, float a_deltatime)
//{
//	Gizmos::addTransform(glm::mat4(1), 5.0f);
//
//	glUseProgram(m_program);
//
//	int view_proj_uniform = glGetUniformLocation(m_program, "projection_view");
//
//	glUniformMatrix4fv(view_proj_uniform, 1, GL_FALSE, (float*)&_gameCamera.getProjectionView());
//
//	for (unsigned int i = 0; i < m_gl_info.size(); ++i)
//	{
//		glBindVertexArray(m_gl_info[i].m_VAO);
//		glDrawElements(GL_TRIANGLES, m_gl_info[i].m_index_count, GL_UNSIGNED_INT, 0);
//	}
//}
//
//void TinyObjSideProject::Update()
//{
//}
//
//void TinyObjSideProject::GameLoop()
//{
//}
//
//void TinyObjSideProject::AddVarToTwBar(TwBar* a_bar)
//{
//	//Add the variables for Tweak bar
//	TwAddVarRW(a_bar, "Light Colour",
//		TW_TYPE_COLOR3F, &m_lightColour[0], "");
//
//	TwAddVarRW(a_bar, "Light Direction",
//		TW_TYPE_DIR3F, &m_lightDir[0], "");
//
//	TwAddVarRW(a_bar, "Specular Power",
//		TW_TYPE_FLOAT, &m_spec, "");
//}
//
//void TinyObjSideProject::GetShaderProgram(GLuint a_program)
//{
//	m_program = a_program;
//}
//
//void TinyObjSideProject::LoadObj()
//{
//	std::vector<tinyobj::shape_t> shapes;
//	std::vector<tinyobj::material_t> materials;
//
//	std::string err = tinyobj::LoadObj(shapes, materials,
//		"./models/stanford/bunny.obj");//
//}