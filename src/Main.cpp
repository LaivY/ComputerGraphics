#include "openGL.h"
#include "Shader.h"
#include "Camera.h"
#include "Main.h"

// GLOBAL
Shader s; Camera c; Light l;

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

	drawAxis();
	drawCube();

	glDisable(GL_DEPTH_TEST);
	/* 그리기 종료 */

	glutSwapBuffers();
}

GLvoid reShape(int w, int h)
{
	glViewport(0, 0, w, h);
}

// CALLBACK
void keyboard(unsigned char key, int x, int y)
{
	camera_keyboard_event(c, key, x, y);
	camera_set_view_matrix(c, s.pid);
	glutPostRedisplay();
}

void motion(int x, int y)
{
	camera_mouse_motion_event(c, x, y);
	camera_set_view_matrix(c, s.pid);
	glutPostRedisplay();
}

// DRAW
void drawAxis()
{
	std::vector<glm::vec3> pos, color;
	glm::vec3 xs = { -3.0,  0.0,  0.0 };
	glm::vec3 xe = {  3.0,  0.0,  0.0 };
	glm::vec3 ys = {  0.0, -3.0,  0.0 };
	glm::vec3 ye = {  0.0,  3.0,  0.0 };
	glm::vec3 zs = {  0.0,  0.0, -3.0 };
	glm::vec3 ze = {  0.0,  0.0,  3.0 };

	pos.push_back(xs);
	pos.push_back(xe);
	pos.push_back(ys);
	pos.push_back(ye);
	pos.push_back(zs);
	pos.push_back(ze);

	glm::vec3 c = { 1.0, 1.0, 1.0 };
	color.push_back(c);
	color.push_back(c);
	color.push_back(c);
	color.push_back(c);
	color.push_back(c);
	color.push_back(c);

	glUseProgram(s.pid);
	s.setBufferData(pos, color);
	glDrawArrays(GL_LINES, 0, 6);
	glUseProgram(0);
}

void drawCube()
{
	float data[] =
	{
		 // 상
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  1.0f,  0.0f,

		 // 하
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f,  0.0f,

		 // 앞
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,  1.0f,

		 // 뒤
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f,  0.0f, 1.0f,

		 // 좌
		-0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,

		 // 우
		 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f,  0.0f,  0.0f,
	};
	
	std::vector<glm::vec3> pos, rgb;
	for (int i = 0; i < sizeof(data) / sizeof(data[0]); i += 6)
	{
		glm::vec3 p = { data[i], data[i + 1], data[i + 2] };
		glm::vec3 c = { data[i + 3], data[i + 4], data[i + 5] };
		
		pos.push_back(p); rgb.push_back(c);
	}

	glUseProgram(s.pid);
	s.setBufferData(pos, rgb);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
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