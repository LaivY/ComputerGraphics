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
KeyValue keyValue;
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
	updateChrPosTimer(NULL);
	updateChrHpTimer(NULL);
	updateItemTimer(NULL);
	updateObsTimer(NULL);

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

void motion(int x, int y)
{
	chr.mouseMotionEvent(c, x, y);
	chr.setCameraViewMatrix(c, s.pid);
	glutPostRedisplay();
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
	updateItems(item);
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

//2.0 거리
void cross_maze(float z)
{
	//파란 교차 구간
	{
		//앞줄
		{
			Obstacles temp3(Cube(glm::vec3(0.4, 0.5, z), 0.5));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(Cube(glm::vec3(0.0, 0.5, z), 0.5));
			obs.push_back(temp3);
		}




		{
			Obstacles temp3(Cube(glm::vec3(-0.8, 0.5, z - 1.4), 0.5));
			obs.push_back(temp3);
		}
	
		{
			Obstacles temp3(Cube(glm::vec3(0.8, 0.5, z - 1.4), 0.5));
			obs.push_back(temp3);
		}
	

	


	}

}

//2.6 거리
void way_3(float z)
{

	//왼쪽
	{
		Obstacles temp3(Cube(glm::vec3(-0.4, 0.2, z), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.2, z - 0.2), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.2, z - 0.6), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.2, z - 1.0), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.2, z - 1.4), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.2, z - 1.8), 0.2));
		obs.push_back(temp);
	}

	//오른쪽
	{
		Obstacles temp3(Cube(glm::vec3(0.4, 0.2, z), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp(Cube(glm::vec3(0.4, 0.2, z - 0.2), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(0.4, 0.2, z - 0.6), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(0.4, 0.2, z - 1.0), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(0.4, 0.2, z - 1.4), 0.2));
		obs.push_back(temp);
	}
	{
		Obstacles temp(Cube(glm::vec3(0.4, 0.2, z - 1.8), 0.2));
		obs.push_back(temp);
	}

	//3차로 끝나는 지점
	{
		{
			Obstacles temp3(HCube(glm::vec3(0, 0.2, z - 2.2), 0.2,0.01));
			obs.push_back(temp3);
		}

	}


}


void side_maze(float z)
{


	{
		Obstacles temp3(Cube(glm::vec3(0.6, 0.4, z), 0.4));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(Cube(glm::vec3(-0.6, 0.4, z), 0.4));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(Cube(glm::vec3(0.6, 0.4, z-1.1), 0.4));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(Cube(glm::vec3(-0.6, 0.4, z-1.1), 0.4));
		obs.push_back(temp3);
	}

	Item a = Heal(glm::vec3(-0.8, 0.3, z - 1.65));
	item.push_back(a);


	{
		Obstacles temp3(Cube(glm::vec3(0.6, 0.4, z - 2.2), 0.4));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(Cube(glm::vec3(-0.6, 0.4, z - 2.2), 0.4));
		obs.push_back(temp3);
	}



	////상하
	//{
	//	Obstacles temp4(VCube(glm::vec3(0.0, 0.1, z - 2.0), 0.2));
	//	obs.push_back(temp4);
	//}

	//아이템











}
void zige(float z)
{
	{
		Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z), 0.2));
		obs.push_back(temp);
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z - 0.4), 0.2));
			obs.push_back(temp);
		}

		{
			Obstacles temp(Cube(glm::vec3(0.8, 0.1, z - 0.4), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z - 0.8), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 0.8), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z - 1.2), 0.2));
			obs.push_back(temp);
		}
	}

	{

		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z - 1.6), 0.2));
			obs.push_back(temp);
		}

	}
	
	Item a = Heal(glm::vec3(-0.8, 0.3, z - 1.6));
	item.push_back(a);


	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z - 2.0), 0.2));
			obs.push_back(temp);
		}

	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z - 2.4), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 2.4), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z - 2.8), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.8, 0.1, z - 2.8), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z - 3.2), 0.2));
			obs.push_back(temp);
		}
	}


	
}
void hzone(float z)
{
	{
		Obstacles temp2(HCube(glm::vec3(-0.0, 0.2, z), 0.2,0.03));
		obs.push_back(temp2);
	}

	{
		Obstacles temp5(HCube(glm::vec3(0.0, 0.2, z - 0.4), 0.2, -0.03));
		obs.push_back(temp5);
	}
	{
		Obstacles temp2(HCube(glm::vec3(-0.0, 0.2, z - 0.8), 0.2, 0.03));
		obs.push_back(temp2);
	}

	{
		Obstacles temp5(HCube(glm::vec3(0.0, 0.2, z - 1.2), 0.2, -0.03));
		obs.push_back(temp5);
	}



}

void jump_1(float z)
{

	

	{
		Obstacles temp3(Cube(glm::vec3(-0.8, 0.4, z-1.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.4, 0.4, z- 1.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.0, 0.4, z- 1.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.4, 0.4, z- 1.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.8, 0.4, z- 1.0), 0.4));
		obs.push_back(temp3);
	}



	{
		Obstacles temp3(Cube(glm::vec3(-0.4, 0.8, z - 2.2), 0.6));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.0, 0.8, z - 2.2), 0.6));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.4, 0.8, z - 2.2), 0.6));
		obs.push_back(temp3);
	}

	
	Item a = Heal(glm::vec3(-0.8, 1.0, z - 3.2));
	item.push_back(a);

	{
		Obstacles temp3(Cube(glm::vec3(-0.8, 0.4, z - 3.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.4, 0.4, z - 3.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.0, 0.4, z - 3.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.4, 0.4, z - 3.0), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.8, 0.4, z - 3.0), 0.4));
		obs.push_back(temp3);
	}
	


}

void jump_2(float z)
{



	{
		Obstacles temp3(Cube(glm::vec3(-0.8, 0.4, z ), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.4, 0.4, z ), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.0, 0.4, z ), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.4, 0.4, z ), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.8, 0.4, z ), 0.4));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(Cube(glm::vec3(-0.8, 0.4, z - 2.4), 0.4));
		obs.push_back(temp3);
	}
	
	{
		Obstacles temp3(Cube(glm::vec3(0.0, 0.8, z - 2.4), 0.8));
		obs.push_back(temp3);
	}


	Item a = Heal(glm::vec3(-0.9, 0.3, z - 3.2));
	item.push_back(a);





}

void jump_3(float z)
{

	{
		Obstacles temp3(HCube(glm::vec3(-0.8, 0.2, z), 0.2,0.03));
		obs.push_back(temp3);
	}





	{
		Obstacles temp3(Cube(glm::vec3(-0.55, 0.4, z-0.8), 0.4));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(-0.0, 0.3, z - 0.8), 0.3));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.55, 0.4, z - 0.8), 0.4));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(Cube(glm::vec3(-0.2, 0.4, z - 2.2), 0.6));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(Cube(glm::vec3(0.2, 0.4, z - 2.2), 0.6));
		obs.push_back(temp3);
	}

	Item a = Heal(glm::vec3(-0.0, 0.3, z - 1.4));
	item.push_back(a);





}


void debug()
{


	//for (int i = 0; i < 10; i++)
	//{
	//	glm::vec3 pos = { rand() % 100 / 100.0 - 0.5, 0.3, -1 };
	//	Item a = Heal(pos);
	//	item.push_back(a);
	//}


	float z = -1;
	int pattern = 0;
	for (int i = 0;i < 10;i++)
	{
		pattern = rand() % 17;
		printf("%d\n",pattern);
		if (pattern == 0 || pattern == 1|| pattern == 2)
		{
			hzone(z);
		}
		else if (pattern == 3 || pattern == 4|| pattern == 5)
		{
			way_3(z);
		}
		else if (pattern == 6 || pattern == 7|| pattern == 8)
		{
			side_maze(z);
		}
		else if (pattern == 9|| pattern == 10|| pattern == 11)
		{
			cross_maze(z);
		}
		else if (pattern == 12|| pattern == 13|| pattern == 14)
		{
			zige(z);
		}
		else if (pattern == 15)
		{
			jump_1(z);
		}
		else if (pattern == 16)
		{
			jump_2(z);
		}
		else if (pattern == 17)
		{
			jump_3(z);
		}





		z -= 5;

		("%d\n", pattern);
	}



	glm::vec3 t = { 1, 2, 3 };
}