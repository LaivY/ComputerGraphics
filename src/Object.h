#pragma once
#include "openGL.h"
#include "Shader.h"
#include <string>
#include <vector>

class Object
{
public:
	// ADDITIONAL
	float x = 0, y = 0, z = 0;
	float angle = 0;

	// ESSENTIAL
	float color[3];	// »ö±ò
	glm::mat4 model; // ¸ðµ¨ º¯È¯ Çà·Ä
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> vertices;
	std::vector<GLuint> uvIndices;
	std::vector<GLuint> vertexIndices;
	std::vector<GLuint> normalIndices;
	BOOL haveData = FALSE;

	// FUNC
	void loadObject(std::string name);
	void drawObject(Shader& s, Camera& c, Light& l);
	void drawObjectWithTexture(Shader& s, Camera& c, std::vector<glm::vec2>& tp);
	void setModelMatrix(glm::mat4 _model) { model = _model; }
	void setColor(float* _color);
	void clear();
};