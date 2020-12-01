#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"

class Cube
{
public:
	// 왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래 순서
	glm::vec3 top[4], bot[4];

	void draw(Shader& s);

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
};