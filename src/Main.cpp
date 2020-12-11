#include "FRAMEWORK/openGL.h"
#include "FRAMEWORK/Shader.h"
#include "FRAMEWORK/Camera.h"
#include "INGAME/Chracter.h"
#include "INGAME/Obstacle.h"
#include "INGAME/Item.h"
#include "INGAME/Painter.h"
#include "keyValues.h"
#include "Main.h"

// GLOBAL
KeyValue keyvalue;
Shader s, _s; Camera c, _c; Character chr;
std::vector<Obstacles> obs; std::vector<Item> item;

void debug();
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

	debug();

	/* 콜백 함수 설정 */
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);

	/* 타이머 함수 설정 */
	updateChrHpTimer(NULL);
	updateItemTimer(NULL);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reShape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(keyvalue.get("Red"), keyvalue.get("Green"), keyvalue.get("Blue"), 1.0);
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
void keyboard(unsigned char key, int x, int y)
{
	chr.keyBoardEvent(c, obs, item, key, x, y);
	chr.update(keyvalue);

	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	chr.keyBoardUpEvent(key, x, y);
	glutPostRedisplay();
}

void motion(int x, int y)
{
	chr.mouseMotionEvent(c, x, y);
	chr.setCameraViewMatrix(c, s.pid);
	glutPostRedisplay();
}

void updateChrHpTimer(int unused)
{
	int hp = chr.getHp();
	if (hp > 0)
		chr.setHp(std::max(hp - 1, 0));

	glutPostRedisplay();
	glutTimerFunc(keyvalue.get("chrHpUpdateInterval"), updateChrHpTimer, NULL);
}

void updateItemTimer(int unused)
{
	updateItems(item);
	glutPostRedisplay();
	glutTimerFunc(50, updateItemTimer, NULL);
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
	keyvalue.set("Red", 0);
	keyvalue.set("Blue", 0);
	keyvalue.set("Green", 0);

	// 캐릭터 속도
	keyvalue.set("chrSpeed", 0.01);

	// 캐릭터 HP 깎이는 간격
	keyvalue.set("chrHpUpdateInterval", 1000);
}

void debug()
{
	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos = { rand() % 100 / 100.0 - 0.5, 0.2, 1 };
		Obstacles temp(Cube(pos, 0.1));
		obs.push_back(temp);
	}

	for (int i = 0; i < 10; i++)
	{
		glm::vec3 pos = { rand() % 100 / 100.0 - 0.5, 0.2, -1 };
		Item temp(Heal(pos, 0.05));
		item.push_back(temp);
	}
}