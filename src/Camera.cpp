#include "Camera.h"
#include "openGL.h"
#include <iostream>

void camera_keyboard_event(Camera& c, unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		c.x += sin(glm::radians(c.xzAngle)) * c.speed;
		c.y +=  sin(glm::radians(c.yAngle)) * c.speed;
		c.z -= cos(glm::radians(c.xzAngle)) * c.speed;
	}
	else if (key == 'a')
	{
		c.x -= sin(glm::radians(c.xzAngle + 90.0)) * c.speed;
		c.z += cos(glm::radians(c.xzAngle + 90.0)) * c.speed;
	}
	else if (key == 's')
	{
		c.x -= sin(glm::radians(c.xzAngle)) * c.speed;
		c.y -=  sin(glm::radians(c.yAngle)) * c.speed;
		c.z += cos(glm::radians(c.xzAngle)) * c.speed;
	}
	else if (key == 'd')
	{
		c.x -= sin(glm::radians(c.xzAngle - 90.0)) * c.speed;
		c.z += cos(glm::radians(c.xzAngle - 90.0)) * c.speed;
	}
	else if (key == 'q')
	{
		c.y += 0.05;
	}
	else if (key == 'e')
	{
		c.y -= 0.05;
	}
}

void camera_mouse_motion_event(Camera& c, int x, int y)
{
	if (c.mx < x - c.sensitivity) // 마우스를 오른쪽으로 움직였을 경우
	{
		c.mx = x;
		c.xzAngle -= 2;
	}
	else if (c.mx > x + c.sensitivity) // 마우스를 오른쪽으로 움직였을 경우
	{
		c.mx = x;
		c.xzAngle += 2;
	}

	if (c.my < y - c.sensitivity) // 마우스를 위로 움직였을 경우
	{
		c.my = y;
		c.yAngle += 1;
		if (c.yAngle > 89)
			c.yAngle = 89;
	}
	else if (c.my > y + c.sensitivity) // 마우스를 아래로 움직였을 경우
	{
		c.my = y;
		c.yAngle -= 1;
		if (c.yAngle < -89)
			c.yAngle = -89;
	}
}

void camera_set_view_matrix(Camera& c, GLuint pid)
{
	glUseProgram(pid);
	glm::vec3 eye = { c.x, c.y, c.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}