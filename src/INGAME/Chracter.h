#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
#include "../FRAMEWORK/Camera.h"
#include "../INGAME/Obstacle.h"
#include "../INGAME/Item.h"
#include "../keyValues.h"
#include <vector>
#include <algorithm>
#define LEFT  0
#define RIGHT 1
#define FRONT 2
#define BACK  3

class Character
{
private:
	/* 캐릭터 이동 관련 변수 */
	int dir = FRONT;
	float speed = 0;
	BOOL isMove = FALSE;
	glm::vec3 hitBox[8];
	glm::vec3 pos = { 0, 0.26, 0 };

	/* 캐릭터 그리기 관련 변수 */
	float angle = 0, aAngle = 0, lAngle = 0, rAngle = 0;

	/* 기타 변수 */
	int hp = 100;
	float dy = 0;

public:
	void draw(Shader& s, Camera& c);

	/* 콜백 함수 */
	void keyBoardEvent(Camera& c, std::vector<Obstacles>& obs, std::vector<Item>& item, unsigned char key, int kx, int ky);
	void keyBoardUpEvent(unsigned char key, int kx, int ky);
	void mouseMotionEvent(Camera& c, int kx, int ky);

	/* 업데이트 함수 */
	void updateHP();
	void updateHitBox();
	void updateSpeed(KeyValue& keyValue);
	void updateTimer(KeyValue& keyValue, Camera& c, std::vector<Obstacles>& obs, std::vector<Item>& item);

	/* 판정 함수 */
	BOOL isGameOver();
	BOOL isCollided(std::vector<Obstacles>& obs, std::vector<Item>& item);

	/* 뷰 변환 */
	void setCameraViewMatrix(Camera& c, GLuint pid);
	void setTopCameraViewMatrix(Camera& _c, GLuint pid);

	/* Getter, Setter */
	glm::vec3 getPos() { return pos; }
	int getHp() { return hp; }
	void setHp(int _hp) { hp = _hp; }
	void setIsMove(BOOL _isMove) { isMove = _isMove; }
};