#pragma once
#include "openGL.h"

class Camera
{
public:
	float radius = 0.5;				// 카메라가 움직이는 원의 반지름
	float xzAngle = 0, yAngle = 0;	// 보고있는 각도

	float mx = 0, my = 0; // 마우스 좌표
	float sensitivity = 5; // 마우스 감도
};