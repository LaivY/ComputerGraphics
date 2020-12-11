#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Heal
{
public:
	// ��ġ, ������
	glm::vec3 pos; float radius;

	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];

	// ȸ�� ����
	float angle = 0;

	Heal(glm::vec3 p, float r)
	{
		pos = p; radius = r;

		top[0] = { p.x - r, p.y + r, p.z - r };
		top[1] = { p.x + r, p.y + r, p.z - r };
		top[2] = { p.x - r, p.y + r, p.z + r };
		top[3] = { p.x + r, p.y + r, p.z + r };

		bot[0] = { p.x - r, p.y - r, p.z - r };
		bot[1] = { p.x + r, p.y - r, p.z - r };
		bot[2] = { p.x - r, p.y - r, p.z + r };
		bot[3] = { p.x + r, p.y - r, p.z + r };
	}

	void draw(Shader& s);
};

// ��� �������� �� class���� ������
class Item
{
public:
	Heal* heal = nullptr;

	Item(){}
	Item(Heal _heal)
	{
		heal = new Heal(_heal);
	}
};

void updateItems(std::vector<Item>& item);