#include "Chracter.h"

void Character::draw(Shader& s, Camera& c)
{
	float cube[] =
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
	for (int i = 0; i < sizeof(cube) / sizeof(cube[0]); i += 3)
	{
		glm::vec3 p = { cube[i], cube[i + 1], cube[i + 2] };
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

	// 카메라 방향에 따라 캐릭터 회전
	GLfloat CHR_GLOBAL_ROTATION_ANGLE = 0;
	switch (dir)
	{
	case LEFT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle + 90;
		break;
	case RIGHT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle - 90;
		break;
	case FRONT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle + 180;
		break;
	case BACK:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle;
		break;
	}

	// 몸
	{
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
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
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
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
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
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
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
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
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 왼쪽 눈
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// 오른쪽 눈
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glUseProgram(0);
}

void Character::update()
{
	// 히트박스 업데이트
	hitBox[0] = { x - 0.025, y + 0.04, z - 0.025 };
	hitBox[1] = { x + 0.025, y + 0.04, z - 0.025 };
	hitBox[2] = { x - 0.025, y + 0.04, z + 0.025 };
	hitBox[3] = { x + 0.025, y + 0.04, z + 0.025 };

	hitBox[4] = { x - 0.025, y - 0.04, z - 0.025 };
	hitBox[5] = { x + 0.025, y - 0.04, z - 0.025 };
	hitBox[6] = { x - 0.025, y - 0.04, z + 0.025 };
	hitBox[7] = { x + 0.025, y - 0.04, z + 0.025 };

	GLfloat CHR_GLOBAL_ROTATION_ANGLE = 0;
	switch (dir)
	{
	case LEFT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle + 90;
		break;
	case RIGHT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle - 90;
		break;
	case FRONT:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle + 180;
		break;
	case BACK:
		CHR_GLOBAL_ROTATION_ANGLE = rAngle;
		break;
	}

	glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	for (int i = 0; i < 8; i++)
	{
		hitBox[i] = t0 * r0 * glm::vec4(hitBox[i], 1);
	}
}

BOOL Character::isCollided(std::vector<Cube>& cube)
{
	for (auto& c : cube)
	{
		float lx = c.top[0].x;
		float rx = c.top[1].x;
		float ty = c.top[0].y;
		float by = c.bot[0].y;
		float fz = c.top[2].z;
		float bz = c.top[0].z;

		std::cout << "x : " << lx << " , " << rx << std::endl;
		std::cout << "y : " << by << " , " << ty << std::endl;
		std::cout << "z : " << bz << " , " << fz << std::endl;


		for (int i = 0; i < 8; i++)
		{
			std::cout << hitBox[i].x << " , " << hitBox[i].y << " , " << hitBox[i].z << std::endl << std::endl;
			if (lx < hitBox[i].x && hitBox[i].x < rx &&
				by < hitBox[i].y && hitBox[i].y < ty &&
				bz < hitBox[i].z && hitBox[i].z < fz)
			{
				return TRUE;
			}
		}
	}
	return FALSE;
}

void chrKeyboardEvent(Character& chr, Camera& c, unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		chr.dir = FRONT;
		chr.angle += 10;
		chr.rAngle = c.xzAngle;
		chr.aAngle = chr.lAngle = 60 * cos(glm::radians(chr.angle));

		chr.x += sin(glm::radians(c.xzAngle)) * chr.speed;
		chr.z -= cos(glm::radians(c.xzAngle)) * chr.speed;
	}
	else if (key == 'a')
	{
		chr.dir = LEFT;
		chr.angle += 10;
		chr.rAngle = c.xzAngle;
		chr.aAngle = chr.lAngle = 60 * cos(glm::radians(chr.angle));

		chr.x -= sin(glm::radians(c.xzAngle + 90)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle + 90)) * chr.speed;
	}
	else if (key == 's')
	{
		chr.dir = BACK;
		chr.angle += 10;
		chr.rAngle = c.xzAngle;
		chr.aAngle = chr.lAngle = 60 * cos(glm::radians(chr.angle));

		chr.x -= sin(glm::radians(c.xzAngle)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle)) * chr.speed;
	}
	else if (key == 'd')
	{
		chr.dir = RIGHT;
		chr.angle += 10;
		chr.rAngle = c.xzAngle;
		chr.aAngle = chr.lAngle = 60 * cos(glm::radians(chr.angle));

		chr.x -= sin(glm::radians(c.xzAngle - 90)) * chr.speed;
		chr.z += cos(glm::radians(c.xzAngle - 90)) * chr.speed;
	}
	chr.update();
}

void chrSetCameraViewMatrix(Character& chr, Camera& c, GLuint pid)
{
	// 카메라 위치
	glm::vec4 pos(0, 0, 0, 1);
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(c.radius * sin(glm::radians(-c.xzAngle)), 0, c.radius * cos(glm::radians(-c.xzAngle))));
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -c.radius * glm::radians(c.yAngle), 0));
	glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(chr.x, chr.y + 0.16, chr.z));
	pos = t2 * t1 * t0 * pos;

	glUseProgram(pid);
	glm::vec3 eye = { pos.x, pos.y, pos.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void chrCameraMouseMotionEvent(Character& chr, Camera& c, int x, int y)
{
	// 마우스를 오른쪽으로 움직였을 경우
	if (c.mx < x - c.sensitivity)
	{
		c.mx = x;
		c.xzAngle -= 2;
	}

	// 마우스를 오른쪽으로 움직였을 경우
	else if (c.mx > x + c.sensitivity)
	{
		c.mx = x;
		c.xzAngle += 2;
	}

	// 마우스를 위로 움직였을 경우
	if (c.my < y - c.sensitivity)
	{
		c.my = y;
		c.yAngle += 1;
		if (c.yAngle > 10)
			c.yAngle = 10;
	}

	// 마우스를 아래로 움직였을 경우
	else if (c.my > y + c.sensitivity)
	{
		c.my = y;
		c.yAngle -= 1;
		if (c.yAngle < -30)
			c.yAngle = -30;
	}
}