#include "Item.h"

void updateItems(std::vector<Item>& item)
{
	for (auto& i : item)
	{
		if (i.heal != nullptr)
		{
			i.heal->angle += 10;
		}
	}
}

void Heal::draw(Shader& s)
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
				c.push_back(glm::vec3(0.9, 0.2, 0.2));
			else
				c.push_back(glm::vec3(1.0, 0.2, 0.2));
		}
	}

	// 모델 변환
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), -pos);
	glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0, 0, 1));
	glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.05 * sin(glm::radians(angle)), 0));
	glm::mat4 t2 = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 model = t2 * t1 * r1 * r0 * t0;

	glUseProgram(s.pid);

	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));
	s.setBufferData(p, c); glDrawArrays(GL_TRIANGLES, 0, 36);

	glUseProgram(0);
}