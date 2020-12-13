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

	/* 게임 설명 */
	printInstructions();

	/* 콜백 함수 설정 */
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);
	glutMouseWheelFunc(wheel);

	/* 타이머 함수 설정 */
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

// 맵
glEnable(GL_DEPTH_TEST);
drawMap(s, c, obs, item, chr);
glDisable(GL_DEPTH_TEST);

// 미니맵
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
	// 확대
	if (direction == 1)
	{
		c.radius -= 0.05;
		c.radius = std::max(0.3f, c.radius);
	}

	// 축소
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

	// 모델, 투영 변환 초기화
	glm::mat4 base(1.0f);
	GLuint model_matrix_location = glGetUniformLocation(pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 50.0f);
	GLuint proj_matrix_location = glGetUniformLocation(pid, "proj");
	glUniformMatrix4fv(proj_matrix_location, 1, GL_FALSE, glm::value_ptr(proj));

	// 뷰 변환 초기화
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

	// 모델, 뷰, 투영 변환 초기화
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
	// 배경색
	keyValue.set("Red", 0);
	keyValue.set("Blue", 0);
	keyValue.set("Green", 0);

	// 캐릭터 속도
	keyValue.set("chrSpeed", 0.05);

	// 캐릭터 HP 깎이는 간격
	keyValue.set("chrHpUpdateInterval", 1000);
}

// ETC
void printInstructions()
{
	std::cout << std::endl;
	std::cout << "┌───────────── ^ㅡ^팀 프로젝트─────────────┐" << std::endl;
	std::cout << "│ WASD\t\t: 이동                     │" << std::endl;
	std::cout << "│ 스페이스바\t: 점프                     │" << std::endl;
	std::cout << "│ 마우스 드래그\t: 카메라 방향 전환         │" << std::endl;
	std::cout << "│ 마우스 휠\t: 확대, 축소               │" << std::endl;
	std::cout << "├──────────────────────────────────────────┤" << std::endl;
	std::cout << "│ 캐릭터의 체력은 계속해서 소모되며,       │" << std::endl;
	std::cout << "│ 캐릭터가 나아갈수록 더 빨리 소모됩니다   │" << std::endl;
	std::cout << "│ 아이템을 획득해 체력을 회복할 수 있습니다│" << std::endl;
	std::cout << "│ 장애물들을 뚫고 최대한 앞으로 가봅시다!  │" << std::endl;
	std::cout << "└──────────────────────────────────────────┘" << std::endl;
}