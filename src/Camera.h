#pragma once
#include "openGL.h"

class Camera
{
public:
	float x = 0, y = 0, z = 5, speed = 0.1; // 카메라 좌표와 이동속도
	float xzAngle = 0, yAngle = 0; // 보고있는 각도

	float mx = 0, my = 0; // 마우스 좌표
	float sensitivity = 5; // 마우스 감도
};

void camera_keyboard_event(Camera& c, unsigned char key, int x, int y);
void camera_mouse_motion_event(Camera& c, int x, int y);
void camera_set_view_matrix(Camera& c, GLuint pid);