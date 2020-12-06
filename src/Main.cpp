#include "FRAMEWORK/openGL.h"
#include "FRAMEWORK/Shader.h"
#include "FRAMEWORK/Camera.h"
#include "INGAME/Chracter.h"
#include "INGAME/Obstacle.h"
#include "Main.h"

// GLOBAL
Shader s; Camera c;
Character chr; std::vector<Obstacles> obs;

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
	iniUniformData(s.pid);
	debug();

	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);

	glutDisplayFunc(drawScene);
	glutReshapeFunc(reShape);
	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* 그리기 시작 */
	glEnable(GL_DEPTH_TEST);

	drawLand();
	chr.draw(s, c);
	for (auto& i : obs)
	{
		if (i.cube != nullptr)
			i.cube->draw(s);
		//i.draw(s);
	}

	glDisable(GL_DEPTH_TEST);
	/* 그리기 종료 */

	glutSwapBuffers();
}

GLvoid reShape(int w, int h)
{
	glViewport(0, 0, w, h);
}

// DRAW
void drawLand()
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
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,

		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,

		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,

		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,

		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,

		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
		0.2, 0.2, 0.2,
	};

	std::vector<glm::vec3> pos, rgb;
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

	glUseProgram(s.pid);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 0.01, 10));
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(scale));
	s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);

	glUseProgram(0);
}

// CALLBACK
void keyboard(unsigned char key, int x, int y)
{
	chr.keyBoardEvent(c, obs, key, x, y);
	chr.setCameraViewMatrix(c, s.pid);
	chr.update();

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

// ini
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

void debug()
{
	Obstacles temp;
	Cube* cube = new Cube(glm::vec3(0, 0.1, -1), 0.2);
	temp.cube = cube;

	obs.push_back(temp);
}