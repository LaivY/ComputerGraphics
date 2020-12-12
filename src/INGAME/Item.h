#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Heal
{
public:
	// 위치, 반지름
	glm::vec3 pos; float radius;

	// 왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래 순서
	glm::vec3 top[4], bot[4];

	// 회전 각도
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