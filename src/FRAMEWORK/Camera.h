#pragma once
#include "openGL.h"

class Camera
{
public:
	//float x = 0, y = 0, z = 3;	// ī�޶� ��ǥ (����������)
	float radius = 0.5;				// ī�޶� �����̴� ���� ������
	float xzAngle = 0, yAngle = 0;	// �����ִ� ����

	float mx = 0, my = 0; // ���콺 ��ǥ
	float sensitivity = 5; // ���콺 ����
};