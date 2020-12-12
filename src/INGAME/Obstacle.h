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

	HCube(glm::vec3 p, float r, float _dx=0.01)
	{
		pos = p; radius = r; dx = _dx;

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

class VCube
{
public:
	glm::vec3 pos; float radius; float dz; float range[2];
	glm::vec3 top[4], bot[4];

	VCube(glm::vec3 p, float r, float _dz=0.01, float _dis=1)
	{
		pos = p; radius = r; dz = _dz;
		range[0] = p.z - _dis; range[1] = p.z + _dis;

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
	VCube* vCube = nullptr;

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
	Obstacles(VCube _vCube)
	{
		vCube = new VCube(_vCube);
	}
};