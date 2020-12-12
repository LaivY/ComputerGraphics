#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
//�Ϲ� ť��
class Cube
{
public:
	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];
	Cube(glm::vec3 p, float r)
	{
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
//�¿� ť��
class HCube
{
public:
	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];
	float dx = 0.00;
	float ddx = 0.002;
	HCube(glm::vec3 p, float r)
	{
		top[0] = { p.x - r, p.y + 2 * r, p.z - r };
		top[1] = { p.x + r, p.y + 2 * r, p.z - r };
		top[2] = { p.x - r, p.y + 2 * r, p.z + r };
		top[3] = { p.x + r, p.y + 2 * r, p.z + r };

		bot[0] = { p.x - r, p.y - r, p.z - r };
		bot[1] = { p.x + r, p.y - r, p.z - r };
		bot[2] = { p.x - r, p.y - r, p.z + r };
		bot[3] = { p.x + r, p.y - r, p.z + r };
	}

	void draw(Shader& s);
};
class H2Cube
{
	
public:
	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];
	float dx = 0.00;
	float ddx = -0.002;
	H2Cube(glm::vec3 p, float r)
	{
		top[0] = { p.x - r, p.y + 2 * r, p.z - r };
		top[1] = { p.x + r, p.y + 2 * r, p.z - r };
		top[2] = { p.x - r, p.y + 2 * r, p.z + r };
		top[3] = { p.x + r, p.y + 2 * r, p.z + r };

		bot[0] = { p.x - r, p.y - r, p.z - r };
		bot[1] = { p.x + r, p.y - r, p.z - r };
		bot[2] = { p.x - r, p.y - r, p.z + r };
		bot[3] = { p.x + r, p.y - r, p.z + r };
	}

	void draw(Shader& s);
};
//���� ť��
class VCube
{
public:
	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];
	float dz = 0.00;
	float ddz = 0.01;
	VCube(glm::vec3 p, float r)
	{
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
//ū ť��
class MageCube
{
public:
	// ������, ��������, ���ʾƷ�, �����ʾƷ� ����
	glm::vec3 top[4], bot[4];
	MageCube(glm::vec3 p, float r)
	{
		top[0] = { p.x - r, p.y + r * 2, p.z - r / 2 };
		top[1] = { p.x + r, p.y + r * 2, p.z - r / 2 };
		top[2] = { p.x - r, p.y + r * 2, p.z + r / 2 };
		top[3] = { p.x + r, p.y + r * 2, p.z + r / 2 };

		bot[0] = { p.x - r, p.y - r * 2, p.z - r / 2 };
		bot[1] = { p.x + r, p.y - r * 2, p.z - r / 2 };
		bot[2] = { p.x - r, p.y - r * 2, p.z + r / 2 };
		bot[3] = { p.x + r, p.y - r * 2, p.z + r / 2 };
	}

	void draw(Shader& s);
};

// ��� ��ֹ��� �� class���� ������
class Obstacles
{
public:
	Cube* cube = nullptr;
	HCube* hcube = nullptr;
	MageCube* mcube = nullptr;
	VCube* vcube = nullptr;
	H2Cube* h2cube = nullptr;
	Obstacles(Cube _cube)
	{
		cube = new Cube(_cube);
		
	}
	Obstacles(HCube _hcube)
	{
		hcube = new HCube(_hcube);

	}
	Obstacles(H2Cube _h2cube)
	{
		h2cube = new H2Cube(_h2cube);

	}
	Obstacles(MageCube _mcube)
	{
		mcube = new MageCube(_mcube);

	}
	Obstacles(VCube _vcube)
	{
		vcube = new VCube(_vcube);

	}

};