#include "Generator.h"

void cross_maze(std::vector<Obstacles>& obs, float z)
{
	Obstacles o0(Cube(glm::vec3(0.4, 0.5, z), 0.5));
	Obstacles o1(Cube(glm::vec3(0.0, 0.5, z), 0.5));
	Obstacles o2(Cube(glm::vec3(-0.8, 0.5, z - 1.4), 0.5));
	Obstacles o3(Cube(glm::vec3(0.8, 0.5, z - 1.4), 0.5));

	obs.push_back(o0);
	obs.push_back(o1);
	obs.push_back(o2);
	obs.push_back(o3);
}

void way_3(std::vector<Obstacles>& obs, float z)
{
	// 좌우
	for (int i = 0; i < 5; i++)
	{
		glm::vec3 lPos = { -0.4, 0.25, z - 0.4 * i };
		glm::vec3 _lPos = { -0.4, 0.65, z - 0.4 * i };
		Obstacles left = Cube(lPos, 0.2);
		Obstacles _left = Cube(_lPos, 0.2);

		glm::vec3 rPos = { 0.4, 0.25, z - 0.4 * i };
		glm::vec3 _rPos = { 0.4, 0.65, z - 0.4 * i };
		Obstacles right = Cube(rPos, 0.2);
		Obstacles _right = Cube(_rPos, 0.2);

		obs.push_back(left);
		obs.push_back(_left);
		obs.push_back(right);
		obs.push_back(_right);
	}

	// 3차로 끝나는 지점
	Obstacles c0(HCube(glm::vec3(0, 0.25, z - 2.0), 0.2, 0.1));
	obs.push_back(c0);
}

void side_maze(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	for (int i = 0; i < 3; i++)
	{
		glm::vec3 lPos = { -0.6, 0.4, z - 1.1 * i };
		Obstacles left = Cube(lPos, 0.4);

		glm::vec3 rPos = { 0.6, 0.4, z - 1.1 * i };
		Obstacles right = Cube(rPos, 0.4);

		obs.push_back(left);
		obs.push_back(right);
	}

	srand((unsigned)time(NULL));

	glm::vec3 iPos = { 0.8, 0.3, z - 1.65 };
	if (rand() % 2)
	{
		iPos.x *= -1;
	}
	if (rand() % 2)
	{
		iPos.z += 1.1;
	}
	Item a = Heal(iPos);
	item.push_back(a);
}

void zige(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	srand((unsigned)time(NULL));

	int reflect = 1;
	if (rand() % 2)
	{
		reflect = -1;
	}

	for (int i = 0; i < 2; i++)
	{
		Obstacles l0 = Cube(glm::vec3(0, 0.1 + 0.4 * i, z), 0.2);
		Obstacles l1 = Cube(glm::vec3(-0.4 * reflect, 0.1 + 0.4 * i, z - 0.4), 0.2);
		Obstacles l2 = Cube(glm::vec3(0.8 * reflect, 0.1 + 0.4 * i, z - 0.4), 0.2);
		Obstacles l3 = Cube(glm::vec3(-0.8 * reflect, 0.1 + 0.4 * i, z - 0.8), 0.2);
		Obstacles l4 = Cube(glm::vec3(0.4 * reflect, 0.1 + 0.4 * i, z - 0.8), 0.2);
		Obstacles l5 = Cube(glm::vec3(0, 0.1 + 0.4 * i, z - 1.2), 0.2);
		Obstacles l6 = Cube(glm::vec3(-0.4 * reflect, 0.1 + 0.4 * i, z - 1.6), 0.2);

		Obstacles r0 = Cube(glm::vec3(0, 0.1 + 0.4 * i, z - 2.0), 0.2);
		Obstacles r1 = Cube(glm::vec3(-0.8 * reflect, 0.1 + 0.4 * i, z - 2.4), 0.2);
		Obstacles r2 = Cube(glm::vec3(0.4 * reflect, 0.1 + 0.4 * i, z - 2.4), 0.2);
		Obstacles r3 = Cube(glm::vec3(-0.4 * reflect, 0.1 + 0.4 * i, z - 2.8), 0.2);
		Obstacles r4 = Cube(glm::vec3(0.8 * reflect, 0.1 + 0.4 * i, z - 2.8), 0.2);
		Obstacles r5 = Cube(glm::vec3(0, 0.1 + 0.4 * i, z - 3.2), 0.2);

		obs.push_back(l0);
		obs.push_back(l1);
		obs.push_back(l2);
		obs.push_back(l3);
		obs.push_back(l4);
		obs.push_back(l5);
		obs.push_back(l6);

		obs.push_back(r0);
		obs.push_back(r1);
		obs.push_back(r2);
		obs.push_back(r3);
		obs.push_back(r4);
		obs.push_back(r5);
	}

	Item a = Heal(glm::vec3(-0.8 * reflect, 0.3, z - 1.6));
	item.push_back(a);
}

void hzone(std::vector<Obstacles>& obs, float z)
{
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos = { 0, 0.3, z - 0.4 * i };
		glm::vec3 _pos = { 0, 0.7, z - 0.4 * i };
		float dx = i % 2 == 0 ? 0.02 + rand() % 25 / 1000.0 : -0.02 - rand() % 25 / 1000.0;
		Obstacles o = HCube(pos, 0.2, dx);
		Obstacles _o = HCube(_pos, 0.2, dx);
		obs.push_back(o);
		obs.push_back(_o);
	}
}

void jump_1(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	for (int i = 0; i < 5; i++)
	{
		glm::vec3 pos = { -0.8 + 0.4 * i, 0.4, z - 1 };
		glm::vec3 _pos = { -0.8 + 0.4 * i, 0.4, z - 3 };
		Obstacles o = Cube(pos, 0.3);
		Obstacles _o = Cube(_pos, 0.3);
		obs.push_back(o);
		obs.push_back(_o);
	}

	for (int i = 0; i < 3; i++)
	{
		glm::vec3 pos = { -0.4 + 0.4 * i, 0.6, z - 2.2 };
		Obstacles o = Cube(pos, 0.6);
		obs.push_back(o);
	}

	Item a = Heal(glm::vec3(-0.8, 1.0, z - 3.2));
	item.push_back(a);
}

void jump_2(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	for (int i = 0; i < 5; i++)
	{
		glm::vec3 pos = { -0.8 + 0.4 * i, 0.4, z };
		Obstacles o = Cube(pos, 0.4);
		obs.push_back(o);
	}

	glm::vec3 p0 = { -0.6, 0.4, z - 2.4 };
	glm::vec3 p1 = { 0, 0.6, z - 2.4 };
	Obstacles o0 = Cube(p0, 0.4);
	Obstacles o1 = Cube(p1, 0.6);
	obs.push_back(o0);
	obs.push_back(o1);

	Item i = Heal(glm::vec3(-0.9, 0.3, z - 3.2));
	item.push_back(i);
}

void jump_3(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	Obstacles o0 = HCube(glm::vec3(-0.8, 0.2, z), 0.2, 0.03);

	Obstacles o1 = Cube(glm::vec3(-0.55, 0.4, z - 0.8), 0.4);
	Obstacles o2 = Cube(glm::vec3(-0.0, 0.3, z - 0.8), 0.3);
	Obstacles o3 = Cube(glm::vec3(0.55, 0.4, z - 0.8), 0.4);

	Obstacles o4 = Cube(glm::vec3(-0.2, 0.6, z - 2.2), 0.6);
	Obstacles o5 = Cube(glm::vec3(0.2, 0.6, z - 2.2), 0.6);

	obs.push_back(o0);
	obs.push_back(o1);
	obs.push_back(o2);
	obs.push_back(o3);
	obs.push_back(o4);
	obs.push_back(o5);

	Item a = Heal(glm::vec3(-0.0, 0.3, z - 1.4));
	item.push_back(a);
}

void genStructure(std::vector<Obstacles>& obs, std::vector<Item>& item, float z)
{
	int percent = rand() % 100;

	if (0 <= percent && percent < 17)
	{
		hzone(obs, z);
	}
	else if (17 <= percent && percent < 34)
	{
		way_3(obs, z);
	}
	else if (34 <= percent && percent < 51)
	{
		side_maze(obs, item, z);
	}
	else if (51 <= percent && percent < 68)
	{
		cross_maze(obs, z);
	}
	else if (68 <= percent && percent < 85)
	{
		zige(obs, item, z);
	}
	else if (85 <= percent && percent < 90)
	{
		jump_1(obs, item, z);
	}
	else if (90 <= percent && percent < 95)
	{
		jump_2(obs, item, z);
	}
	else if (95 <= percent && percent < 100)
	{
		jump_3(obs, item, z);
	}
}