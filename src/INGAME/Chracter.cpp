#include "Chracter.h"

float CUBE_DATA[] =
{
	// 상
	-1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,

	// 하
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	-1.0, -1.0,  1.0,
	-1.0, -1.0, -1.0,

	// 앞
	-1.0, -1.0,  1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0,
	1.0,  1.0,  1.0,
	-1.0,  1.0,  1.0,
	-1.0, -1.0,  1.0,

	// 뒤
	-1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0,  1.0, -1.0,
	1.0,  1.0, -1.0,
	-1.0,  1.0, -1.0,
	-1.0, -1.0, -1.0,

	// 좌
	-1.0,  1.0,  1.0,
	-1.0,  1.0, -1.0,
	-1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,
	-1.0, -1.0,  1.0,
	-1.0,  1.0,  1.0,

	// 우
	1.0,  1.0,  1.0,
	1.0,  1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0, -1.0,
	1.0, -1.0,  1.0,
	1.0,  1.0,  1.0
};

void Character::drawCharacter(Shader& s, Camera& c)
{
	float color[] =
	{
		// 상
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,

		// 하
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,

		// 앞
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,

		// 뒤
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,

		// 좌
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,

		// 우
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
	};

	float eye_color[] =
	{
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,

		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0, 0, 0,
	};

	// 배열 -> 벡터 변환
	std::vector<glm::vec3> pos, rgb, _rgb;
	for (int i = 0; i < sizeof(CUBE_DATA) / sizeof(CUBE_DATA[0]); i += 3)
	{
		glm::vec3 p = { CUBE_DATA[i], CUBE_DATA[i + 1], CUBE_DATA[i + 2] };
		pos.push_back(p);
	}
	for (int i = 0; i < sizeof(color) / sizeof(color[0]); i += 3)
	{
		glm::vec3 c = { color[i], color[i + 1], color[i + 2] };
		rgb.push_back(c);
	}
	for (int i = 0; i < sizeof(eye_color) / sizeof(eye_color[0]); i += 3)
	{
		glm::vec3 _c = { eye_color[i], eye_color[i + 1], eye_color[i + 2] };
		_rgb.push_back(_c);
	}

	glUseProgram(s.pid);

	// 몸
	{
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.05, 0.08, 0.05));
		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t0 * s0 * r0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 왼쪽 팔
	{
		// 스케일
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		// 흔들기
		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(aAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		// 위치
		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.06, -0.01, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 오른쪽 팔
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-aAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.06, -0.01, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 왼쪽 다리
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(lAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.02, -0.12, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 오른쪽 다리
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-lAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02, -0.12, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 왼쪽 눈
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 오른쪽 눈
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-c.xzAngle), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glUseProgram(0);
}

void chr_keyboard_event(Character& chr, Camera& c, unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		chr.x += sin(glm::radians(c.xzAngle + 180)) * chr.speed;
		chr.z -= cos(glm::radians(c.xzAngle + 180)) * chr.speed;

		chr.angle += 10;
		chr.aAngle = 60 * cos(glm::radians(chr.angle));
	}
	else if (key == 'a')
	{
		chr.x -= sin(glm::radians(c.xzAngle + 90 + 180)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle + 90 + 180)) * chr.speed;
	}
	else if (key == 's')
	{
		chr.x -= sin(glm::radians(c.xzAngle + 180)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle + 180)) * chr.speed;
	}
	else if (key == 'd')
	{
		chr.x -= sin(glm::radians(c.xzAngle - 90 + 180)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle - 90 + 180)) * chr.speed;
	}
}

void chr_set_camera_view_matrix(Character& chr, Camera& c, GLuint pid)
{
	// 카메라 위치 : 캐릭터 기준 반지름이 0.6인 원
	glm::vec4 pos(0.5 * sin(glm::radians(-c.xzAngle + 180)), 0.16, 0.5 * cos(glm::radians(-c.xzAngle + 180)), 1);

	// 캐릭터 뒤통수가 보이는 방향으로 회전
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(chr.x, chr.y, chr.z));

	//pos = t0 * r0 * pos;
	pos = t0 * pos;

	glUseProgram(pid);
	glm::vec3 eye = { pos.x, pos.y, pos.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle + 180)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle + 180)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void chr_camera_mouse_motion_event(Character& chr, Camera& c, int x, int y)
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

	//if (c.my < y - c.sensitivity) // 마우스를 위로 움직였을 경우
	//{
	//	c.my = y;
	//	c.yAngle += 1;
	//	if (c.yAngle > 89)
	//		c.yAngle = 89;
	//}
	//else if (c.my > y + c.sensitivity) // 마우스를 아래로 움직였을 경우
	//{
	//	c.my = y;
	//	c.yAngle -= 1;
	//	if (c.yAngle < -89)
	//		c.yAngle = -89;
	//}
	//std::cout << c.yAngle << std::endl;
}