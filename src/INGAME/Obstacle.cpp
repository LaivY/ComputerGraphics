#include "Obstacle.h"
#include <iostream>

void Cube::draw(Shader& s)
{
	std::vector<glm::vec3> p, c;

	// 큐브 위치 설정
	{
		// 상
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// 하
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// 좌
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// 우
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// 앞
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// 뒤
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// 색깔 설정
	{
		for (int i = 0; i < 36; i++)
		{
			if (i < 12)
				c.push_back(glm::vec3(0.8, 0.2, 0.2));
			else if (12 <= i && i < 24)
				c.push_back(glm::vec3(0.2, 0.8, 0.2));
			else
				c.push_back(glm::vec3(0.2, 0.2, 0.8));
		}
	}

	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
}
void HCube::draw(Shader& s)
{
	std::vector<glm::vec3> p, c;

	// 큐브 위치 설정
	{
		// 상
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// 하
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// 좌
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// 우
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// 앞
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// 뒤
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// 색깔 설정
	{
		for (int i = 0; i < 36; i++)
		{
			if (i < 12)
				c.push_back(glm::vec3(0.8, 0.2, 0.2));
			else if (12 <= i && i < 24)
				c.push_back(glm::vec3(0.2, 0.8, 0.2));
			else
				c.push_back(glm::vec3(0.2, 0.2, 0.8));
		}
	}

	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
}
void H2Cube::draw(Shader& s)
{
	std::vector<glm::vec3> p, c;

	// 큐브 위치 설정
	{
		// 상
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// 하
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// 좌
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// 우
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// 앞
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// 뒤
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// 색깔 설정
	{
		for (int i = 0; i < 36; i++)
		{
			if (i < 12)
				c.push_back(glm::vec3(0.8, 0.2, 0.2));
			else if (12 <= i && i < 24)
				c.push_back(glm::vec3(0.2, 0.8, 0.2));
			else
				c.push_back(glm::vec3(0.2, 0.2, 0.8));
		}
	}

	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
}
void VCube::draw(Shader& s)
{
	std::vector<glm::vec3> p, c;

	// 큐브 위치 설정
	{
		// 상
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// 하
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// 좌
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// 우
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// 앞
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// 뒤
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// 색깔 설정
	{
		for (int i = 0; i < 36; i++)
		{
			if (i < 12)
				c.push_back(glm::vec3(0.8, 0.2, 0.2));
			else if (12 <= i && i < 24)
				c.push_back(glm::vec3(0.2, 0.8, 0.2));
			else
				c.push_back(glm::vec3(0.2, 0.2, 0.8));
		}
	}

	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
}
void MageCube::draw(Shader& s)
{
	std::vector<glm::vec3> p, c;

	// 큐브 위치 설정
	{
		// 상
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// 하
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// 좌
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// 우
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// 앞
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// 뒤
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// 색깔 설정
	{
		for (int i = 0; i < 36; i++)
		{
			if (i < 12)
				c.push_back(glm::vec3(0.8, 0.2, 0.2));
			else if (12 <= i && i < 24)
				c.push_back(glm::vec3(0.2, 0.8, 0.2));
			else
				c.push_back(glm::vec3(0.2, 0.2, 0.8));
		}
	}

	glUseProgram(s.pid);
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
}