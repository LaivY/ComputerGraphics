#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
#include "../FRAMEWORK/Camera.h"
#include "../INGAME/Obstacle.h"
#include "../INGAME/Item.h"
#include "../keyValues.h"
#include <vector>

#define LEFT  0
#define RIGHT 1
#define FRONT 2
#define BACK  3

class Character
{
private:
	int hp = 100;											// ĳ���� ü��
	int dir = FRONT; float speed = 0;					// ĳ���� ����, �̵��ӵ�
	glm::vec3 pos = { 0, 0.16, 0 }; glm::vec3 hitBox[8];	// ĳ���� ��ǥ, ��Ʈ�ڽ�
	float angle = 0, aAngle = 0, lAngle = 0, rAngle = 0;    // Ÿ�̸�, ��, �ٸ�, ȸ�� ����

public:
	void draw(Shader& s, Camera& c);
	void update(KeyValue& keyValue);
	void keyBoardEvent(Camera& c, std::vector<Obstacles>& obs, std::vector<Item>& item, unsigned char key, int kx, int ky);
	void keyBoardUpEvent(unsigned char key, int kx, int ky);
	void mouseMotionEvent(Camera& c, int kx, int ky);
	void setCameraViewMatrix(Camera& c, GLuint pid);
	void setTopCameraViewMatrix(Camera& _c, GLuint pid);
	BOOL isCollided(std::vector<Obstacles>& obs, std::vector<Item>& item);

	glm::vec3 getPos() { return pos; }
	int getHp() { return hp; }
	void setHp(int _hp) { hp = _hp; }
};