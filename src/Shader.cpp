#define _CRT_SECURE_NO_WARNINGS
#include "Shader.h"

CHAR* Shader::readShader(std::string file)
{
	std::ifstream i;
	std::string str = "";

	i.open(file);
	if (i.is_open())
	{
		while (!i.eof())
		{
			std::string tmp;
			std::getline(i, tmp);
			str += tmp + "\n";
		}
		i.close();
	}
	else
	{
		std::cout << "[오류] " << file << "파일을 찾을 수 없습니다." << std::endl;
	}

	char* result = new char[str.length() + 1];
	std::strcpy(result, str.c_str());
	return result;
}

void Shader::loadShaders(std::string vertexShaderFile, std::string fragmentShaderFile)
{
	GLchar* vSrc = readShader(vertexShaderFile);
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vSrc, NULL);
	glCompileShader(vs);

	GLchar* fSrc = readShader(fragmentShaderFile);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fSrc, NULL);
	glCompileShader(fs);

	// 검사
	GLint result; GLchar err[512];
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vs, 512, NULL, err);
		std::cerr << "Err : vertex Shader Compile error\n" << err << std::endl;
	}
	else
		std::cout << "Compile Vertex Shader OK." << std::endl;

	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fs, 512, NULL, err);
		std::cerr << "Err : fragment Shader Compile error\n" << err << std::endl;
	}
	else
		std::cout << "Compile Fragment Shader OK." << std::endl;

	// 링크
	pid = glCreateProgram();
	glAttachShader(pid, vs);
	glAttachShader(pid, fs);
	glLinkProgram(pid);

	// 링크 후에 삭제
	glDeleteShader(vs);
	glDeleteShader(fs);

	// 검사
	glGetProgramiv(pid, GL_LINK_STATUS, &result);
	if (!result)
		std::cout << "LINK FAIL" << std::endl;
	else
		std::cout << "Link Shader OK." << std::endl;
}

void Shader::setBufferData(std::vector<glm::vec3> pos, std::vector<glm::vec3> color)
{
	// 생성
	if (VAO == -1)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &pVBO);
	}

	// 위치
	if (pVBO == -1)
		glGenBuffers(1, &pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), &pos[0], GL_STATIC_DRAW);

	// 색상
	if (cVBO == -1)
		glGenBuffers(1, &cVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * color.size(), &color[0], GL_STATIC_DRAW);

	// vPos
	GLint pAttribute = glGetAttribLocation(pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	// vColor
	GLint cAttribute = glGetAttribLocation(pid, "vColor");
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(cAttribute);
}

void Shader::setBufferDataWithEBO(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& color, std::vector<GLuint>& index)
{
	// 해당 쉐이더 사용
	glUseProgram(pid);

	// VAO 생성 및 바인딩
	if (VAO == -1)
		glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// 위치
	if (pVBO == -1)
		glGenBuffers(1, &pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), &pos[0], GL_STATIC_DRAW);

	// 색상
	if (cVBO == -1)
		glGenBuffers(1, &cVBO);
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * color.size(), &color[0], GL_STATIC_DRAW);

	// 인덱스 :: 위치
	if (EBO == -1)
		glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * index.size(), &index[0], GL_STATIC_DRAW);

	// vPos
	GLint pAttribute = glGetAttribLocation(pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pAttribute);

	// vColor
	GLint cAttribute = glGetAttribLocation(pid, "vColor");
	glBindBuffer(GL_ARRAY_BUFFER, cVBO);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(cAttribute);
}

void Shader::setBufferDataWithLight(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norm, glm::vec3& oRGB, Camera& c, Light& l)
{
	if (VAO == -1)
		glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	if (pVBO == -1)
		glGenBuffers(1, &pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), &pos[0], GL_STATIC_DRAW);

	if (NBO == -1)
		glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * norm.size(), &norm[0], GL_STATIC_DRAW);

	// pos
	GLint pAttribute = glGetAttribLocation(pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(pAttribute);

	// normal
	GLint nAttribute = glGetAttribLocation(pid, "vNormal");
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glVertexAttribPointer(nAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(nAttribute);

	// 카메라 위치
	GLuint viewPosLocation = glGetUniformLocation(pid, "viewPos");
	glUniform3f(viewPosLocation, c.x, c.y, c.z);

	// 조명 위치
	GLuint lightPosLocation = glGetUniformLocation(pid, "lightPos");
	glUniform3f(lightPosLocation, l.x, l.y, l.z);

	// 조명 색
	GLuint lightColorLocation = glGetUniformLocation(pid, "lightColor");
	glUniform3f(lightColorLocation, l.r, l.g, l.b);

	// 오브젝트 색
	GLuint objColorLocation = glGetUniformLocation(pid, "objectColor");
	glUniform3f(objColorLocation, oRGB.x, oRGB.y, oRGB.z);
}

void Shader::setBufferDataWithTexture(std::vector<glm::vec3>& pos, std::vector<glm::vec3>& norm, std::vector<glm::vec2>& uv)
{
	// 생성
	if (VAO == -1)
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &pVBO);
	}

	// 위치
	if (pVBO == -1)
		glGenBuffers(1, &pVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), &pos[0], GL_STATIC_DRAW);

	// 노멀
	if (NBO == -1)
		glGenBuffers(1, &NBO);
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * norm.size(), &norm[0], GL_STATIC_DRAW);

	// 텍스쳐
	if(TBO == -1)
		glGenBuffers(1, &TBO);
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uv.size(), &uv[0], GL_STATIC_DRAW);

	// vPos
	GLint pAttribute = glGetAttribLocation(pid, "vPos");
	glBindBuffer(GL_ARRAY_BUFFER, pVBO);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(pAttribute);

	// vNormal
	GLint cAttribute = glGetAttribLocation(pid, "vNormal");
	glBindBuffer(GL_ARRAY_BUFFER, NBO);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(cAttribute);

	// vTexCoord
	GLint tAttribute = glGetAttribLocation(pid, "vTexCoord");
	glBindBuffer(GL_ARRAY_BUFFER, TBO);
	glVertexAttribPointer(tAttribute, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(tAttribute);
}