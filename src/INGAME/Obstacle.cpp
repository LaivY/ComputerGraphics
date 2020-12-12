#include "Obstacle.h"
#include <iostream>

void Obstacles::draw(Shader& s)
{
	// ��Ʈ�ڽ� ����
	glm::vec3 top[4], bot[4];
	if (cube != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			top[i] = cube->top[i];
			bot[i] = cube->bot[i];
		}
	}
	else if (hCube != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			top[i] = hCube->top[i];
			bot[i] = hCube->bot[i];
		}
	}
	else if (vCube != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			top[i] = vCube->top[i];
			bot[i] = vCube->bot[i];
		}
	}

	std::vector<glm::vec3> p, c;

	// ť�� ��ġ ����
	{
		// ��
		p.push_back(top[1]);
		p.push_back(top[2]);
		p.push_back(top[3]);

		p.push_back(top[2]);
		p.push_back(top[1]);
		p.push_back(top[0]);

		// ��
		p.push_back(bot[3]);
		p.push_back(bot[2]);
		p.push_back(bot[0]);

		p.push_back(bot[0]);
		p.push_back(bot[1]);
		p.push_back(bot[3]);

		// ��
		p.push_back(top[2]);
		p.push_back(top[0]);
		p.push_back(bot[0]);

		p.push_back(top[2]);
		p.push_back(bot[0]);
		p.push_back(bot[2]);

		// ��
		p.push_back(top[1]);
		p.push_back(top[3]);
		p.push_back(bot[1]);

		p.push_back(top[3]);
		p.push_back(bot[3]);
		p.push_back(bot[1]);

		// ��
		p.push_back(top[2]);
		p.push_back(bot[2]);
		p.push_back(bot[3]);

		p.push_back(top[3]);
		p.push_back(top[2]);
		p.push_back(bot[3]);

		// ��
		p.push_back(top[1]);
		p.push_back(top[0]);
		p.push_back(bot[1]);

		p.push_back(top[0]);
		p.push_back(bot[0]);
		p.push_back(bot[1]);
	}

	// ���� ����
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

void Obstacles::update()
{
	// �¿� ť�� ������Ʈ
	if (hCube != nullptr)
	{
		// ���� ���� �Ѿ�ٸ�
		if (hCube->top[1].x <= -1)
		{
			hCube->dx = abs(hCube->dx);
		}

		// ������ ���� �Ѿ�ٸ�
		else if (hCube->top[0].x >= 1)
		{
			hCube->dx = -abs(hCube->dx);
		}

		for (int i = 0; i < 4; i++)
		{
			hCube->pos.x += hCube->dx;
			hCube->top[i].x += hCube->dx;
			hCube->bot[i].x += hCube->dx;
		}
	}

	// �յ� ť�� ������Ʈ
	else if (vCube != nullptr)
	{
		// ���� �Ÿ� �̻� ������ �̵��ߴٸ�
		if (vCube->pos.z < vCube->range[0])
		{
			vCube->dz = abs(vCube->dz);
		}

		// ������ ���� �Ѿ�ٸ�
		else if (vCube->pos.z > vCube->range[1])
		{
			vCube->dz = -abs(vCube->dz);
		}

		for (int i = 0; i < 4; i++)
		{
			vCube->pos.z += vCube->dz;
			vCube->top[i].z += vCube->dz;
			vCube->bot[i].z += vCube->dz;
		}
	}

	glutPostRedisplay();
}