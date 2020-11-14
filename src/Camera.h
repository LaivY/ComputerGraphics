#pragma once
#include "openGL.h"

class Camera
{
public:
	float x = 0, y = 0, z = 5, speed = 0.1; // ī�޶� ��ǥ�� �̵��ӵ�
	float xzAngle = 0, yAngle = 0; // �����ִ� ����

	float mx = 0, my = 0; // ���콺 ��ǥ
	float sensitivity = 5; // ���콺 ����
};

void camera_keyboard_event(Camera& c, unsigned char key, int x, int y);
void camera_mouse_motion_event(Camera& c, int x, int y);
void camera_set_view_matrix(Camera& c, GLuint pid);