#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
#include "../FRAMEWORK/Camera.h"
#include "../INGAME/Obstacle.h"
#include <vector>

#define LEFT  0
#define RIGHT 1
#define FRONT 2
#define BACK  3

class Character
{
public:
	int dir = FRONT; float speed = 0.01;					// ĳ���� ����, �̵��ӵ�
	float x = 0, y = 0.16, z = 0; glm::vec3 hitBox[8];		// ĳ���� ��ǥ, ��Ʈ�ڽ�
	float angle = 0, aAngle = 0, lAngle = 0, rAngle = 0;    // Ÿ�̸�, ��, �ٸ�, ȸ�� ����

	void draw(Shader& s, Camera& c);
	void update();
	BOOL isCollided(std::vector<Cube>& cube);
};

void chrKeyboardEvent(Character& chr, Camera& c, unsigned char key, int x, int y);
void chrSetCameraViewMatrix(Character& chr, Camera& c, GLuint pid);
void chrCameraMouseMotionEvent(Character& chr, Camera& c, int x, int y);