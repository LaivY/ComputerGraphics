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

/* �ݹ��Լ� */
void Character::keyBoardEvent(Camera& c, std::vector<Obstacles>& obs, std::vector<Item>& item, unsigned char key, int kx, int ky)
{
	if (key == 'w')
	{
		dir = FRONT;
		isMove = TRUE;
	}
	else if (key == 'a')
	{
		dir = LEFT;
		isMove = TRUE;
	}
	else if (key == 's')
	{
		dir = BACK;
		isMove = TRUE;
	}
	else if (key == 'd')
	{
		dir = RIGHT;
		isMove = TRUE;
	}
	else if (key == ' ' && !dy)
	{
		dy = 0.08;
	}
}

void Character::keyBoardUpEvent(unsigned char key, int kx, int ky)
{
	// ��, �ٸ� ���� �ʱ�ȭ
	if (key == 'w' || key == 'a' || key == 's' || key == 'd')
	{
		angle = 90;
		aAngle = 60 * cos(glm::radians(angle));
		lAngle = 60 * cos(glm::radians(angle));
		isMove = FALSE;
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

/* ������Ʈ �Լ� */
void Character::updateHP()
{
	if (hp > 0)
		hp = std::max(hp - 1, 0);
}

void Character::updateHitBox()
{
	hitBox[0] = { -0.10, 0.09, -0.05 };
	hitBox[1] = {  0.10, 0.09, -0.05 };
	hitBox[2] = { -0.10, 0.09,  0.05 };
	hitBox[3] = {  0.10, 0.09,  0.05 };

	hitBox[4] = { -0.10, -0.18, -0.05 };
	hitBox[5] = {  0.10, -0.18, -0.05 };
	hitBox[6] = { -0.10, -0.18,  0.05 };
	hitBox[7] = {  0.10, -0.18,  0.05 };

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

void Character::updateSpeed(KeyValue& keyValue)
{
	// ĳ���� ��ġ�� ���� �� ����
	if (-2 <= pos.z && pos.z < -1)
	{
		// ĳ���� �ӵ� ����
		if (keyValue.get("chrSpeed") < 0.05)
		{
			keyValue.set("chrSpeed", 0.05);
		}
	}
	speed = keyValue.get("chrSpeed");
}

void Character::updateTimer(KeyValue& keyValue, Camera& c, std::vector<Obstacles>& obs, std::vector<Item>& item)
{
	// ����
	pos.y += dy;

	// ��Ʈ�ڽ� ������Ʈ
	updateHitBox();

	// �ӵ� ������Ʈ
	updateSpeed(keyValue);

	// ������ ������Ʈ
	if (!isCollided(obs, item) && isMove)
	{
		if (dir == FRONT)
		{
			angle += 10;
			rAngle = c.xzAngle;
			aAngle = lAngle = 60 * cos(glm::radians(angle));

			pos.x += sin(glm::radians(c.xzAngle)) * speed;
			pos.z -= cos(glm::radians(c.xzAngle)) * speed;
		}
		else if (dir == LEFT)
		{
			angle += 10;
			rAngle = c.xzAngle;
			aAngle = lAngle = 60 * cos(glm::radians(angle));

			pos.x -= sin(glm::radians(c.xzAngle + 90)) * speed;
			pos.z += cos(glm::radians(c.xzAngle + 90)) * speed;
		}
		else if (dir == BACK)
		{
			angle += 10;
			rAngle = c.xzAngle;
			aAngle = lAngle = 60 * cos(glm::radians(angle));

			pos.x -= sin(glm::radians(c.xzAngle)) * speed;
			pos.z += cos(glm::radians(c.xzAngle)) * speed;
		}
		else if (dir == RIGHT)
		{
			angle += 10;
			rAngle = c.xzAngle;
			aAngle = lAngle = 60 * cos(glm::radians(angle));

			pos.x -= sin(glm::radians(c.xzAngle - 90)) * speed;
			pos.z += cos(glm::radians(c.xzAngle - 90)) * speed;
		}
		glutPostRedisplay();
	}

	// ���� ����
	if (isGameOver())
	{
		int grade = -pos.z * 10;
		std::cout << "���� : " << grade << std::endl;

		dir = FRONT;
		pos = { 0, 0.26, 0 }; dy = 0; hp = 100;
		angle = 0, aAngle = 0, lAngle = 0, rAngle = 0;

		c.xzAngle = 0; c.yAngle = 0;
	}
}

/* ���� �Լ� */
BOOL Character::isGameOver()
{
	if (pos.y < -5)
	{
		return TRUE;
	}
	if (hp <= 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Character::isCollided(std::vector<Obstacles>& obs, std::vector<Item>& item)
{
	BOOL isFalling = FALSE;
	BOOL isCollided = FALSE;

	// ĳ���� �¿�, ����, �յ� ��ǥ
	float lx = std::min(hitBox[0].x, hitBox[1].x);
	float rx = std::max(hitBox[0].x, hitBox[1].x);
	float ty = std::max(hitBox[0].y, hitBox[4].y);
	float by = std::min(hitBox[0].y, hitBox[4].y);
	float fz = std::max(hitBox[0].z, hitBox[2].z);
	float bz = std::min(hitBox[0].z, hitBox[2].z);

	// �� ������ ������ ������ ���
	if ((hitBox[0].x < -1 && hitBox[1].x < -1) ||
		(hitBox[0].x > 1 && hitBox[1].x > 1))
		isFalling = TRUE;

	// y���� ���� ���� �� ���� ���� ���
	if (pos.y > 0.26)
		isFalling = TRUE;

	// ��ֹ�
	float knockBackDistance = 0.025;
	for (auto& o : obs)
	{
		// �浹 üũ�� ����� ���� ����
		float _lx, _rx;
		float _ty, _by;
		float _fz, _bz;
		glm::vec3 top[4], bot[4], center; float radius;

		// ť�� ����
		if (o.cube != nullptr)
		{
			// �¿���Ͼյ�
			_lx = o.cube->top[0].x;
			_rx = o.cube->top[1].x;
			_ty = o.cube->top[0].y;
			_by = o.cube->bot[0].y;
			_fz = o.cube->top[2].z;
			_bz = o.cube->top[0].z;
			for (int i = 0; i < 4; i++)
			{
				top[i] = o.cube->top[i];
				bot[i] = o.cube->bot[i];
			}
			center = o.cube->pos;
			radius = o.cube->radius;
		}

		// �¿�ť�� ����
		else if (o.hCube != nullptr)
		{
			_lx = o.hCube->top[0].x;
			_rx = o.hCube->top[1].x;
			_ty = o.hCube->top[0].y;
			_by = o.hCube->bot[0].y;
			_fz = o.hCube->top[2].z;
			_bz = o.hCube->top[0].z;
			for (int i = 0; i < 4; i++)
			{
				top[i] = o.hCube->top[i];
				bot[i] = o.hCube->bot[i];
			}
			center = o.hCube->pos;
			radius = o.hCube->radius;
		}

		// �յ�ť�� ����
		else if (o.vCube != nullptr)
		{
			_lx = o.vCube->top[0].x;
			_rx = o.vCube->top[1].x;
			_ty = o.vCube->top[0].y;
			_by = o.vCube->bot[0].y;
			_fz = o.vCube->top[2].z;
			_bz = o.vCube->top[0].z;
			for (int i = 0; i < 4; i++)
			{
				top[i] = o.vCube->top[i];
				bot[i] = o.vCube->bot[i];
			}
			center = o.vCube->pos;
			radius = o.vCube->radius;
		}

		/* �������� �浹���� ���� */

		// ����� �浹�ߴٸ�
		for (int i = 0; i < 8; i++)
		{
			if (_lx < hitBox[i].x && hitBox[i].x < _rx &&
				_ty <= by && by < _ty + 0.03 &&
				_bz < hitBox[i].z && hitBox[i].z < _fz)
			{
				dy = 0;
				pos.y = center.y + radius + 0.18;
				isFalling = FALSE;
			}
		}

		// ��Ʈ�ڽ��� ���� ť�� �ȿ� �ִٸ�
		for (int i = 0; i < 8; i++)
		{
			if (_lx < hitBox[i].x && hitBox[i].x < _rx &&
				_by < hitBox[i].y && hitBox[i].y < _ty &&
				_bz < hitBox[i].z && hitBox[i].z < _fz)
			{
				// �ո�� �浹�ߴٸ�
				if (pos.z > _fz)
				{
					pos.z += knockBackDistance;
					isCollided = TRUE;
				}
				// ���ʰ� �浹�ߴٸ�
				else if (pos.x < _lx)
				{
					pos.x -= knockBackDistance;
					isCollided = TRUE;
				}
				// �����ʰ� �浹�ߴٸ�
				else if (pos.x > _rx)
				{
					pos.x += knockBackDistance;
					isCollided = TRUE;
				}
				// �޸�� �浹�ߴٸ�
				else if (pos.z < _bz)
				{
					pos.z -= knockBackDistance;
					isCollided = TRUE;
				}
				// �밢�� �浹
				else
				{
					pos.x += knockBackDistance * sin(glm::radians(rAngle + 180));
					pos.z -= knockBackDistance * cos(glm::radians(rAngle + 180));
					isCollided = TRUE;
				}

				if (isCollided)
					goto ITEM_CHECK;
			}
		}

		// ť���� ���� ��Ʈ�ڽ� �ȿ� �ִٸ�
		for (int i = 0; i < 4; i++)
		{
			if (lx < top[i].x && top[i].x < rx &&
				by < top[i].y && top[i].y < ty &&
				bz < top[i].z && top[i].z < fz)
			{
				pos.x += knockBackDistance * sin(glm::radians(rAngle + 180));
				pos.z -= knockBackDistance * cos(glm::radians(rAngle + 180));
				isCollided = TRUE;
			}

			else if (lx < bot[i].x && bot[i].x < rx &&
				by < bot[i].y && bot[i].y < ty &&
				bz < bot[i].z && bot[i].z < fz)
			{
				pos.x += knockBackDistance * sin(glm::radians(rAngle + 180));
				pos.z -= knockBackDistance * cos(glm::radians(rAngle + 180));
				isCollided = TRUE;
			}
		}
	}

	// ������
	ITEM_CHECK:
	for (int i = 0; i < item.size(); i++)
	{
		// ü����
		if (item[i].heal != nullptr)
		{
			float _lx = item[i].heal->top[0].x;
			float _rx = item[i].heal->top[1].x;
			float _ty = item[i].heal->top[0].y;
			float _by = item[i].heal->bot[0].y;
			float _fz = item[i].heal->top[2].z;
			float _bz = item[i].heal->top[0].z;

			for (int j = 0; j < 8; j++)
			{
				BOOL isCollidedWithItem = FALSE;

				// ��Ʈ�ڽ��� �� ���� ������ �ȿ� �ִٸ�
				if (_lx < hitBox[j].x && hitBox[j].x < _rx &&
					_by < hitBox[j].y && hitBox[j].y < _ty &&
					_bz < hitBox[j].z && hitBox[j].z < _fz)
					isCollidedWithItem = TRUE;

				// ĳ������ ������ ������ �ȿ� �ִٸ�
				if (_lx < pos.x && pos.x < _rx &&
					_by < pos.y && pos.y < _ty &&
					_bz < pos.z && pos.z < _fz)
					isCollidedWithItem = TRUE;

				// �����۰� �浹�ߴٸ�
				if (isCollidedWithItem)
				{
					setHp(100);
					delete item[i].heal;
					std::vector<Item>::const_iterator iter = item.begin();
					item.erase(iter + i);
					goto FALLING_CHECK;
				}
			}
		}
	}

	// y�� ����
	FALLING_CHECK:
	if (isFalling && !isCollided)
	{
		dy -= 0.008;
		glutPostRedisplay();
	}

	// ����
	for (int i = 0; i < 8; i++)
		if (-0.05 <= hitBox[i].y - 0.01 && hitBox[i].y - 0.01 < 0.05 && !isFalling)
		{
			dy = 0; pos.y = 0.26;
			break;
		}

	return isCollided;
}

/* �� ��ȯ */
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
	glm::mat4 t1 = glm::translate(glm::mat4(1.0f), glm::vec3(0, 2, 0));
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