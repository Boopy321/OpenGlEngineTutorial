#pragma once
#include "gl_core_4_4.h"
#include <vector>
#include <string>
#include "glm\glm.hpp"
#include "VertexStructure.h"

using namespace std;

struct ObjectData {
	vector<glm::vec3> s_vertices, s_normals, s_colours;
	vector<glm::vec2> s_texCoords;
	vector<GLuint> vIndices, uIndices, nIndices;
};

class ObjectLoader
{
public:
	ObjectLoader(string objName, std::vector<Vertex>& outVertices);
	~ObjectLoader();

	inline ObjectData* getModel() const { return m_object; }
	GLenum getRenderMode() const;
private:
	///Material Struct
	struct Material {
		string s_name;
		glm::vec3 s_colour;
	};

	vector< Material* > m_materials;
	Material* m_currentMaterial;
	ObjectData* m_object;
	bool hasUV, hasNormals, isQuads, indexChecked;

	string parseString(string src, string code);
	glm::vec2 parseVec2(string src, string code);
	glm::vec3 parseVec3(string src, string code);

	void addIndices(string str);
	void checkIndices(string str);
	void loadObjects(string objPath);
	void loadMaterials(string matPath);
};

