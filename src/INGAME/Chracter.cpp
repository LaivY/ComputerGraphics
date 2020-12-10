#include "Chracter.h"

void Character::draw(Shader& s, Camera& c)
{
	float cube[] =
	{
		// ��
		-1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,

		// ��
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		-1.0, -1.0,  1.0,
		-1.0, -1.0, -1.0,

		// ��
		-1.0, -1.0,  1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0,
		1.0,  1.0,  1.0,
		-1.0,  1.0,  1.0,
		-1.0, -1.0,  1.0,

		// ��
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0, -1.0,
		1.0,  1.0, -1.0,
		-1.0,  1.0, -1.0,
		-1.0, -1.0, -1.0,

		// ��
		-1.0,  1.0,  1.0,
		-1.0,  1.0, -1.0,
		-1.0, -1.0, -1.0,
		-1.0, -1.0, -1.0,
		-1.0, -1.0,  1.0,
		-1.0,  1.0,  1.0,

		// ��
		1.0,  1.0,  1.0,
		1.0,  1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, -1.0,  1.0,
		1.0,  1.0,  1.0
	};

	float color[] =
	{
		// ��
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,

		// ��
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,
		0.9, 0.9, 0.9,

		// ��
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,
		0.8, 0.8, 0.8,

		// ��
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,
		0.6, 0.6, 0.6,

		// ��
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,
		0.75, 0.75, 0.75,

		// ��
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

	// �迭 -> ���� ��ȯ
	std::vector<glm::vec3> _pos, rgb, _rgb;
	for (int i = 0; i < sizeof(cube) / sizeof(cube[0]); i += 3)
	{
		glm::vec3 p = { cube[i], cube[i + 1], cube[i + 2] };
		_pos.push_back(p);
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

	// ī�޶� ���⿡ ���� ĳ���� ȸ��
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

	// ��
	{
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.05, 0.08, 0.05));
		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), pos);
		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t0 * s0 * r0));
		s.setBufferData(_pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ���� ��
	{
		// ������
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		// ����
		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(aAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		// ��ġ
		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.06, -0.01, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(_pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ������ ��
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-aAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.06, -0.01, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(_pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ���� �ٸ�
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(lAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(0.02, -0.12, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(_pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ������ �ٸ�
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.01, 0.04, 0.01));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -0.02, 0));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-lAngle), glm::vec3(1, 0, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0.02, 0));

		glm::mat4 t2 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02, -0.12, 0));
		glm::mat4 r1 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t3 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t3 * r1 * t2 * t1 * r0 * t0 * s0));
		s.setBufferData(_pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ���� ��
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(_pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	// ������ ��
	{
		glm::mat4 s0 = glm::scale(glm::mat4(1.0f), glm::vec3(0.005, 0.02, 0.005));

		glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(-0.02, 0.03, 0.05));
		glm::mat4 r0 = glm::rotate(glm::mat4(1.0f), glm::radians(-CHR_GLOBAL_ROTATION_ANGLE), glm::vec3(0, 1, 0));
		glm::mat4 t1 = glm::translate(glm::mat4(1.0f), pos);

		GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
		glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(t1 * r0 * t0 * s0));
		s.setBufferData(_pos, _rgb); glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glUseProgram(0);
}

void Character::update()
{
	// ��Ʈ�ڽ� ������Ʈ
	hitBox[0] = { -0.05, 0.04, -0.05 };
	hitBox[1] = {  0.05, 0.04, -0.05 };
	hitBox[2] = { -0.05, 0.04,  0.05 };
	hitBox[3] = {  0.05, 0.04,  0.05 };

	hitBox[4] = { -0.05, -0.04, -0.05 };
	hitBox[5] = {  0.05, -0.04, -0.05 };
	hitBox[6] = { -0.05, -0.04,  0.05 };
	hitBox[7] = {  0.05, -0.04,  0.05 };

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
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), pos);
	for (int i = 0; i < 8; i++)
	{
		hitBox[i] = t0 * r0 * glm::vec4(hitBox[i], 1);
	}
}

void Character::keyBoardEvent(Camera& c, std::vector<Obstacles>& obs, unsigned char key, int kx, int ky)
{
	if (isCollided(obs))
	{
		return;
	}

	if (key == 'w')
	{
		dir = FRONT;
		angle += 10;
		rAngle = c.xzAngle;
		aAngle = lAngle = 60 * cos(glm::radians(angle));

		pos.x += sin(glm::radians(c.xzAngle)) * speed;
		pos.z -= cos(glm::radians(c.xzAngle)) * speed;
	}
	else if (key == 'a')
	{
		dir = LEFT;
		angle += 10;
		rAngle = c.xzAngle;
		aAngle = lAngle = 60 * cos(glm::radians(angle));

		pos.x -= sin(glm::radians(c.xzAngle + 90)) * speed;
		pos.z += cos(glm::radians(c.xzAngle + 90)) * speed;
	}
	else if (key == 's')
	{
		dir = BACK;
		angle += 10;
		rAngle = c.xzAngle;
		aAngle = lAngle = 60 * cos(glm::radians(angle));

		pos.x -= sin(glm::radians(c.xzAngle)) * speed;
		pos.z += cos(glm::radians(c.xzAngle)) * speed;
	}
	else if (key == 'd')
	{
		dir = RIGHT;
		angle += 10;
		rAngle = c.xzAngle;
		aAngle = lAngle = 60 * cos(glm::radians(angle));

		pos.x -= sin(glm::radians(c.xzAngle - 90)) * speed;
		pos.z += cos(glm::radians(c.xzAngle - 90)) * speed;
	}
}

void Character::keyBoardUpEvent(unsigned char key, int kx, int ky)
{
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		angle = 90;
		aAngle = 60 * cos(glm::radians(angle));
		lAngle = 60 * cos(glm::radians(angle));
	}
}

void Character::mouseMotionEvent(Camera& c, int kx, int ky)
{
	// ���콺�� ���������� �������� ���
	if (c.mx < kx - c.sensitivity)
	{
		c.mx = kx;
		c.xzAngle -= 2;
	}

	// ���콺�� ���������� �������� ���
	else if (c.mx > kx + c.sensitivity)
	{
		c.mx = kx;
		c.xzAngle += 2;
	}

	// ���콺�� ���� �������� ���
	if (c.my < ky - c.sensitivity)
	{
		c.my = ky;
		c.yAngle += 1;
		if (c.yAngle > 10)
			c.yAngle = 10;
	}

	// ���콺�� �Ʒ��� �������� ���
	else if (c.my > ky + c.sensitivity)
	{
		c.my = ky;
		c.yAngle -= 1;
		if (c.yAngle < -30)
			c.yAngle = -30;
	}
}

void Character::setCameraViewMatrix(Camera& c, GLuint pid)
{
	// ī�޶� ��ġ
	glm::vec4 _eye(0, 0, 0, 1);
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), glm::vec3(c.radius * sin(glm::radians(-c.xzAngle)), 0, c.radius * cos(glm::radians(-c.xzAngle))));
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, -c.radius * glm::radians(c.yAngle), 0));
	glm::mat4 t2 = glm::translate(glm::mat4(1.0f), pos + glm::vec3(0, 0.16, 0));
	_eye = t2 * t1 * t0 * _eye;

	glUseProgram(pid);
	glm::vec3 eye = { _eye.x, _eye.y, _eye.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

void Character::setTopCameraViewMatrix(Camera& _c, GLuint pid)
{
	// ī�޶� ��ġ
	glm::vec4 _eye(0, 0, 0, 1);
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), pos);
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 1, 0));
	_eye = t1 * t0 * _eye;

	glUseProgram(pid);
	glm::vec3 eye = { _eye.x, _eye.y, _eye.z };
	glm::vec3 at = { 0, -1, 0 };
	glm::vec3 up = { 0, 0, -1 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));
	glUseProgram(0);
}

BOOL Character::isCollided(std::vector<Obstacles>& obs)
{
	for (auto& o : obs)
	{
		// ť�� �浹 üũ
		if (o.cube != nullptr)
		{
			float lx = o.cube->top[0].x;
			float rx = o.cube->top[1].x;
			float ty = o.cube->top[0].y;
			float by = o.cube->bot[0].y;
			float fz = o.cube->top[2].z;
			float bz = o.cube->top[0].z;

			for (int i = 0; i < 8; i++)
			{
				if (lx < hitBox[i].x && hitBox[i].x < rx &&
					by < hitBox[i].y && hitBox[i].y < ty &&
					bz < hitBox[i].z && hitBox[i].z < fz)
				{
					// �ո�� �浹�ߴٸ�
					if (pos.z > fz)
						pos.z += 0.025;
					// ���ʰ� �浹�ߴٸ�
					if (pos.x < lx)
						pos.x -= 0.025;
					// �����ʰ� �浹�ߴٸ�
					if (pos.x > rx)
						pos.x += 0.025;
					// �޸�� �浹�ߴٸ�
					if (pos.z < bz)
						pos.z -= 0.025;
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}