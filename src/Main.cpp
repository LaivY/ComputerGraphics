#include "FRAMEWORK/openGL.h"
#include "FRAMEWORK/Shader.h"
#include "FRAMEWORK/Camera.h"
#include "INGAME/Chracter.h"
#include "Main.h"

// GLOBAL
Shader s; Camera c; Character chr;

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

	glutKeyboardFunc(keyboard);
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
	chr.drawCharacter(s, c);

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

	glUseProgram(s.pid);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 0.01, 1));
	GLuint model_matrix_location = glGetUniformLocation(s.pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(scale));
	s.setBufferData(pos, rgb); glDrawArrays(GL_TRIANGLES, 0, 36);

	s.setBufferData(pos, rgb);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glUseProgram(0);
}

// CALLBACK
void keyboard(unsigned char key, int x, int y)
{
	chr_keyboard_event(chr, c, key, x, y);
	chr_set_camera_view_matrix(chr, c, s.pid);
	glutPostRedisplay();
}

void motion(int x, int y)
{
	chr_camera_mouse_motion_event(chr, c, x, y);
	chr_set_camera_view_matrix(chr, c, s.pid);
	glutPostRedisplay();
}

// ini
void iniUniformData(GLuint pid)
{
	glUseProgram(pid);

	glm::mat4 base(1.0f);
	GLuint model_matrix_location = glGetUniformLocation(pid, "model");
	glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, glm::value_ptr(base));

	glm::vec3 eye = { c.x, c.y, c.z };
	glm::vec3 at = { sin(glm::radians(c.xzAngle)), sin(glm::radians(c.yAngle)), -cos(glm::radians(c.xzAngle)) };
	glm::vec3 up = { 0, cos(glm::radians(c.yAngle)), 0 };
	glm::mat4 view = glm::lookAt(eye, eye + at, up);
	GLuint view_matrix_location = glGetUniformLocation(pid, "view");
	glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 50.0f);
	GLuint proj_matrix_location = glGetUniformLocation(pid, "proj");
	glUniformMatrix4fv(proj_matrix_location, 1, GL_FALSE, glm::value_ptr(proj));

	glUseProgram(0);
}