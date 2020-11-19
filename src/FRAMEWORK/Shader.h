#pragma once
#include "openGL.h"
#include "Camera.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Shader
{
public:
	GLuint pid = -1;
	GLuint VAO = -1, pVBO = -1, cVBO = -1, EBO = -1, NBO = -1, TBO = -1;

	CHAR* readShader(std::string file);
	void loadShaders(std::string vertexShaderFile, std::string fragmentShaderFile);
	void setBufferData(std::vector<glm::vec3> pos, std::vector<glm::vec3> color);
	void setBufferDataWithEBO(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& color, std::vector<GLuint>& index);
	void setBufferDataWithTexture(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norm, std::vector<glm::vec2>& uv);
};