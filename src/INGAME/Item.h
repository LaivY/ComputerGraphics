#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Heal
{
public:
	// 위치
	glm::vec3 pos;

	// 왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래 순서
	glm::vec3 top[4], bot[4];

	// 회전 각도
	float angle = 0;

	Heal(glm::vec3 p)
	{
		pos = p;

		top[0] = { p.x - 0.05, p.y + 0.05, p.z - 0.05 };
		top[1] = { p.x + 0.05, p.y + 0.05, p.z - 0.05 };
		top[2] = { p.x - 0.05, p.y + 0.05, p.z + 0.05 };
		top[3] = { p.x + 0.05, p.y + 0.05, p.z + 0.05 };

		bot[0] = { p.x - 0.05, p.y - 0.05, p.z - 0.05 };
		bot[1] = { p.x + 0.05, p.y - 0.05, p.z - 0.05 };
		bot[2] = { p.x - 0.05, p.y - 0.05, p.z + 0.05 };
		bot[3] = { p.x + 0.05, p.y - 0.05, p.z + 0.05 };
	}

	void draw(Shader& s);
};

// 모든 아이템은 이 class에서 관리됨
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