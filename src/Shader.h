#pragma once
#include "openGL.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Light
{
public:
	float x = 0, y = 3, z = 0;
	float r = 1, g = 1, b = 1;
};

class Shader
{
public:
	GLuint pid = -1;
	GLuint VAO = -1, pVBO = -1, cVBO = -1, EBO = -1, NBO = -1, TBO = -1;

	CHAR* readShader(std::string file);
	void loadShaders(std::string vertexShaderFile, std::string fragmentShaderFile);
	void setBufferData(std::vector<glm::vec3> pos, std::vector<glm::vec3> color);
	void setBufferDataWithEBO(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& color, std::vector<GLuint>& index);
	void setBufferDataWithLight(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norm, glm::vec3& oRGB, Camera& c, Light& l);
	void setBufferDataWithTexture(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norm, std::vector<glm::vec2>& uv);
};

void iniUniformData(GLuint pid);