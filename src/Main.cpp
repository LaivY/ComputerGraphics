#include "FRAMEWORK/openGL.h"
#include "FRAMEWORK/Shader.h"
#include "FRAMEWORK/Camera.h"
#include "INGAME/Chracter.h"
#include "INGAME/Obstacle.h"
#include "INGAME/Item.h"
#include "INGAME/Painter.h"
#include "INGAME/Generator.h"
#include "keyValues.h"
#include "Main.h"

// GLOBAL
KeyValue keyValue;
Shader s, _s; Camera c, _c; Character chr;
std::vector<Obstacles> obs; std::vector<Item> item;

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("TEAM ^-^");
	glewInit();

	s.loadShaders("../shader/vertex.glsl", "../shader/fragment.glsl");
	_s.loadShaders("../shader/vertex.glsl", "../shader/fragment.glsl");
	iniUniformData(s.pid);
	iniUniformData2(_s.pid);
	iniKeyValues();

	/* ���� ���� */
	printInstructions();

	/* �ݹ� �Լ� ���� */
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);
	glutMouseWheelFunc(wheel);

	/* Ÿ�̸� �Լ� ���� */
	updateChrPosTimer(NULL);
	updateChrHpTimer(NULL);
	updateItemTimer(NULL);
	updateObsTimer(NULL);
	updateGenTimer(NULL);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reShape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(keyValue.get("Red"), keyValue.get("Green"), keyValue.get("Blue"), 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ��
glEnable(GL_DEPTH_TEST);
drawMap(s, c, obs, item, chr);
glDisable(GL_DEPTH_TEST);

// �̴ϸ�
drawMiniMabBGR(_s);
glEnable(GL_DEPTH_TEST);
drawMiniMab(s, _c, obs, item, chr);
glDisable(GL_DEPTH_TEST);

// UI
drawHPBar(_s, chr.getHp());
drawMiniMabEdge(_s);
drawHPBarEdge(_s);

glutSwapBuffers();
}

GLvoid reShape(int w, int h)
{
	glViewport(0, 0, w, h);
}

// CALLBACK
void motion(int x, int y)
{
	chr.mouseMotionEvent(c, x, y);
	chr.setCameraViewMatrix(c, s.pid);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	chr.keyBoardEvent(c, obs, item, key, x, y);
	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	chr.keyBoardUpEvent(key, x, y);
	glutPostRedisplay();
}

void wheel(int wheel, int direction, int x, int y)
{
	// Ȯ��
	if (direction == 1)
	{
		c.radius -= 0.05;
		c.radius = std::max(0.3f, c.radius);
	}

	// ���
	else if (direction == -1)
	{
		c.radius += 0.05;
		c.radius = std::min(1.0f, c.radius);
	}
}

void updateChrPosTimer(int unused)
{
	chr.updateTimer(keyValue, c, obs, item);
	glutTimerFunc(30, updateChrPosTimer, NULL);
}

void updateChrHpTimer(int unused)
{
	chr.updateHP();
	glutTimerFunc(keyValue.get("chrHpUpdateInterval"), updateChrHpTimer, NULL);
}

void updateItemTimer(int unused)
{
	for (auto& i : item)
	{
		i.update();
	}
	glutPostRedisplay();
	glutTimerFunc(50, updateItemTimer, NULL);
}

void updateObsTimer(int unused)
{
	for (auto& o : obs)
	{
		o.update();
	}
	glutTimerFunc(30, updateObsTimer, NULL);
}

void updateGenTimer(int unused)
{
	int z = -chr.getPos().z;

	if (z % 8 == 0)
	{
		if (keyValue.get("chr" + std::to_string(z)) != 1)
		{
			genStructure(obs, item, -z - 8);
			keyValue.set("chr" + std::to_string(z), 1);
		}

		if (keyValue.get("chr" + std::to_string(z + 8)) != 1)
		{
			genStructure(obs, item, -z - 16);
			keyValue.set("chr" + std::to_string(z + 8), 1);
		}
	}
	glutTimerFunc(10, updateGenTimer, NULL);
}

// INI
void iniUniformData(GLuint pid)
{
	glUseProgram(pid);

	// ��, ���� ��ȯ �ʱ�ȭ
	glm::mat4 base(1.0f);
	GLuint model_matrix_location = glGetUniformLocation(pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 50.0f);
	GLuint proj_matrix_location = glGetUniformLocation(pid, "proj");
	glUniformMatrix4fv(proj_matrix_location, 1, GL_FALSE, glm::value_ptr(proj));

	// �� ��ȯ �ʱ�ȭ
	glm::vec4 pos(0.5 * sin(glm::radians(-c.xzAngle)), 0.16, 0.5 * cos(glm::radians(-c.xzAngle)), 1);
	glm::mat4 t0 = glm::translate(glm::mat4(1.0f), chr.getPos());
	pos = t0 * pos;

	glm::vec3 eye = { pos.x, pos.y, pos.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));

	glUseProgram(0);
}

void iniUniformData2(GLuint pid)
{
	glUseProgram(pid);

	// ��, ��, ���� ��ȯ �ʱ�ȭ
	glm::mat4 base(1.0f);
	GLuint model_matrix_location = glGetUniformLocation(pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	GLuint proj_matrix_location = glGetUniformLocation(pid, "proj");
	glUniformMatrix4fv(proj_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	glUseProgram(0);
}

void iniKeyValues()
{
	// ����
	keyValue.set("Red", 0);
	keyValue.set("Blue", 0);
	keyValue.set("Green", 0);

	// ĳ���� �ӵ�
	keyValue.set("chrSpeed", 0.05);

	// ĳ���� HP ���̴� ����
	keyValue.set("chrHpUpdateInterval", 1000);
}

// ETC
void printInstructions()
{
	std::cout << std::endl;
	std::cout << "���������������������������� ^��^�� ������Ʈ����������������������������" << std::endl;
	std::cout << "�� WASD\t\t: �̵�                     ��" << std::endl;
	std::cout << "�� �����̽���\t: ����                     ��" << std::endl;
	std::cout << "�� ���콺 �巡��\t: ī�޶� ���� ��ȯ         ��" << std::endl;
	std::cout << "�� ���콺 ��\t: Ȯ��, ���               ��" << std::endl;
	std::cout << "����������������������������������������������������������������������������������������" << std::endl;
	std::cout << "�� ĳ������ ü���� ����ؼ� �Ҹ�Ǹ�,       ��" << std::endl;
	std::cout << "�� ĳ���Ͱ� ���ư����� �� ���� �Ҹ�˴ϴ�   ��" << std::endl;
	std::cout << "�� �������� ȹ���� ü���� ȸ���� �� �ֽ��ϴ٦�" << std::endl;
	std::cout << "�� ��ֹ����� �հ� �ִ��� ������ �����ô�!  ��" << std::endl;
	std::cout << "����������������������������������������������������������������������������������������" << std::endl;
}