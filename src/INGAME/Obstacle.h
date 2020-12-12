#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Cube
{
public:
	// ����, ������
	glm::vec3 pos; float radius;

	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];

	Cube(glm::vec3 p, float r)
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
};

class HCube
{
public:
	// ����, ������, �̵���
	glm::vec3 pos; float radius; float dx;

	// �⺻ ����
	glm::vec3 top[4], bot[4];

	HCube(glm::vec3 p, float r, float _speed=0.01)
	{
		pos = p; radius = r; dx = _speed;

		top[0] = { p.x - r, p.y + r, p.z - r };
		top[1] = { p.x + r, p.y + r, p.z - r };
		top[2] = { p.x - r, p.y + r, p.z + r };
		top[3] = { p.x + r, p.y + r, p.z + r };

		bot[0] = { p.x - r, p.y - r, p.z - r };
		bot[1] = { p.x + r, p.y - r, p.z - r };
		bot[2] = { p.x - r, p.y - r, p.z + r };
		bot[3] = { p.x + r, p.y - r, p.z + r };
	}
};

// ��� ��ֹ��� �� class���� ������
class Obstacles
{
public:
	Cube* cube = nullptr;
	HCube* hCube = nullptr;

	void draw(Shader& s);
	void update();

	Obstacles(Cube _cube)
	{
		cube = new Cube(_cube);
	}
	Obstacles(HCube _hCube)
	{
		hCube = new HCube(_hCube);
	}
};