//#pragma once
//class FlyCamera;
//
//#include <vector>
//#include "Vertex.h"
//#include "AntTweakBar.h"
//#include <GLFW\glfw3.h>
//#include <GLFW\glfw3.h>
//
//
//struct OpenGLInfo
//{
//	unsigned int m_VAO;
//	unsigned int m_VBO;
//	unsigned int m_IBO;
//	unsigned int m_index_count;
//};
//
//typedef struct
//{
//	std::vector<float> positions;
//	std::vector<float> normals;
//	std::vector<float> texcoords;
//	std::vector<unsigned int> indices;
//	std::vector<int> material_ids;
//} mesh_t;
//
//
//typedef struct
//{
//	std::string name;
//	mesh_t mesh;
//} shape_t;
//
//class TinyObjSideProject
//{
//
//public:
//	TinyObjSideProject();
//	~TinyObjSideProject();
//
//	void ImageLoad();
//
//	void Draw(FlyCamera &_gameCamera, float a_deltatime);
//	void Update();
//	void GameLoop();
//	void LoadObj();
//	void AddVarToTwBar(TwBar* a_bar);
//	void GetShaderProgram(GLuint a_program);
//
//	void CreateOpenGlBuffers(std::vector<tinyobj::shape_t>& shapes);
//	
//private:
//
//	unsigned int m_texture;
//	unsigned int m_program;
//
//	std::vector<OpenGLInfo> m_gl_info;////
//	int m_imageWidth, m_imageHeight, m_imageFormat;
//	std::string m_path;
//	glm::vec3 m_lightDir;
//	glm::vec3 m_lightColour;
//	float m_spec;
//};
//
//
//
//
