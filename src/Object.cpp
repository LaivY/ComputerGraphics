#define _CRT_SECURE_NO_WARNINGS
#include "Object.h"
#include "Shader.h"

void Object::loadObject(std::string name)
{
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec3> temp_normals;

	FILE* f = fopen(name.c_str(), "r");
	if (f == NULL)
	{
		std::cout << "해당 파일을 열 수 없습니다." << name << std::endl;
		return;
	}
	while (TRUE)
	{
		char lineHeader[128];
		int res = fscanf(f, "%s", lineHeader);
		if (res == EOF)
			break;

		// else : parse lineHeader
		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(f, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(f, "%f %f\n", &uv.x, &uv.y);
			uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(f, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				std::cout << "정해진 형식과 맞지않습니다!" << std::endl;
				return;
			}
			for (int i = 0; i < 3; i++)
			{
				uvIndices.push_back(uvIndex[i]);
				vertexIndices.push_back(vertexIndex[i] - 1);
				normalIndices.push_back(normalIndex[i]);
			}
		}
	}
	fclose(f);
	haveData = TRUE;
	std::cout << "'" << name << "'를 성공적으로 불러왔습니다." << std::endl;
}

void Object::drawObject(Shader& s, Camera& c, Light& l)
{
	if (haveData == FALSE)
	{
		std::cout << "데이터가 없습니다." << std::endl;
		return;
	}

	// 모델링 변환 적용
	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));
	glUseProgram(0);

	///////////////////////////////////////////////////////

	// 해당 쉐이더 사용
	glUseProgram(s.pid);

	// VAO 생성 및 바인딩
	if (s.VAO == -1)
		glGenVertexArrays(1, &s.VAO);
	glBindVertexArray(s.VAO);

	// 정점
	if (s.pVBO == -1)
		glGenBuffers(1, &s.pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, s.pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	
	// 노말 버퍼
	if (s.NBO == -1)
		glGenBuffers(1, &s.NBO);
	glBindBuffer(GL_ARRAY_BUFFER, s.NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

	// 정점 인덱스
	if (s.EBO == -1)
		glGenBuffers(1, &s.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexIndices.size(), &vertexIndices[0], GL_STATIC_DRAW);

	// vPos
	GLint pAttribute = glGetAttribLocation(s.pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, s.pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pAttribute);

	// vNormal
	GLint nAttribute = glGetAttribLocation(s.pid, "vNormal");
	glBindBuffer(GL_ARRAY_BUFFER, s.NBO);
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(nAttribute);

	// 카메라 위치
	GLuint viewPosLocation = glGetUniformLocation(s.pid, "viewPos");
	glUniform3f(viewPosLocation, c.x, c.y, c.z);

	// 조명 위치
	GLuint lightPosLocation = glGetUniformLocation(s.pid, "lightPos");
	glUniform3f(lightPosLocation, l.x, l.y, l.z);

	// 조명 색
	GLuint lightColorLocation = glGetUniformLocation(s.pid, "lightColor");
	glUniform3f(lightColorLocation, l.r, l.g, l.b);

	// 오브젝트 색
	GLuint objColorLocation = glGetUniformLocation(s.pid, "objectColor");
	glUniform3f(objColorLocation, color[0], color[1], color[2]);

	///////////////////////////////////////////////////////

	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
	glBindVertexArray(0);
}

void Object::drawObjectWithTexture(Shader& s, Camera& c, std::vector<glm::vec2>& tp)
{
	// 모델링 변환 적용
	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));
	glUseProgram(0);

	///////////////////////////////////////////////////////

	// 해당 쉐이더 사용
	glUseProgram(s.pid);

	// VAO 생성 및 바인딩
	if (s.VAO == -1)
		glGenVertexArrays(1, &s.VAO);
	glBindVertexArray(s.VAO);

	// 정점
	if (s.pVBO == -1)
		glGenBuffers(1, &s.pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, s.pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// 노말 버퍼
	if (s.NBO == -1)
		glGenBuffers(1, &s.NBO);
	glBindBuffer(GL_ARRAY_BUFFER, s.NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);

	// 텍스쳐 좌표
	GLuint TBO;
	glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * tp.size(), &tp[0], GL_STATIC_DRAW);

	// 정점 인덱스
	if (s.EBO == -1)
		glGenBuffers(1, &s.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * vertexIndices.size(), &vertexIndices[0], GL_STATIC_DRAW);

	// vPos
	GLint pAttribute = glGetAttribLocation(s.pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, s.pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pAttribute);

	// vNormal
	GLint nAttribute = glGetAttribLocation(s.pid, "vNormal");
	glBindBuffer(GL_ARRAY_BUFFER, s.NBO);
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(nAttribute);

	// vTexCoord
	GLint tAttribute = glGetAttribLocation(s.pid, "vTexCoord");
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(tAttribute);

	///////////////////////////////////////////////////////

	glDrawElements(GL_TRIANGLES, vertexIndices.size(), GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void Object::setColor(float* _color)
{
	for (int i = 0; i < 3; i++)
		color[i] = _color[i];
}

void Object::clear()
{
	std::vector<glm::vec2>().swap(uvs);
	std::vector<glm::vec3>().swap(normals);
	std::vector<glm::vec3>().swap(vertices);
	std::vector<GLuint>().swap(vertexIndices);
	haveData = FALSE;
}