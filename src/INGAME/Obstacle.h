#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Cube
{
public:
	// 중점, 반지름
	glm::vec3 pos; float radius;

	// 왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래 순서
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
	// 중점, 반지름, 이동량
	glm::vec3 pos; float radius; float dx;

	// 기본 변수
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

// 모든 장애물은 이 class에서 관리됨
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