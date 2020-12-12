#include "FRAMEWORK/openGL.h"
#include "FRAMEWORK/Shader.h"
#include "FRAMEWORK/Camera.h"
#include "INGAME/Chracter.h"
#include "INGAME/Obstacle.h"
#include "INGAME/Item.h"
#include "INGAME/Painter.h"
#include "keyValues.h"
#include "Main.h"
#include <algorithm>
// GLOBAL
KeyValue keyvalue;
Shader s, _s; Camera c, _c; Character chr;
std::vector<Obstacles> obs; std::vector<Item> item;


float h1dz = 0.00;


float h2dz = 0.00;

float h1ddx = 0.002;
float ddz = 0.002;
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
	updateHObsTimer(NULL);
	updateH2ObsTimer(NULL);
	updateVObsTimer(NULL);
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
float h2dx = 0;
float h2ddx = 0.002;
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
void updateHObsTimer(int unused)
{
	
	
	for (auto& o : obs)
	{
		if (o.hcube != nullptr)
		{
			
			if (o.hcube->dx < 0.0)
			{
				o.hcube->ddx = -o.hcube->ddx;
				 

			}
			else if (o.hcube->dx > 1.6)
			{
				o.hcube->ddx = -o.hcube->ddx;

			}

			o.hcube->dx += o.hcube->ddx;
			printf("b : %f\n", o.hcube->ddx);


			for (int i = 0; i < 4; i++)
			{
				o.hcube->bot[i].x += o.hcube->ddx;
				o.hcube->top[i].x += o.hcube->ddx;

			}
			printf("re : %f\n", o.hcube->dx);




		}

	}

	glutPostRedisplay();
	glutTimerFunc(10, updateHObsTimer, NULL);
}
void updateH2ObsTimer(int unused)
{
	
	for (auto& o : obs)
	{
		if (o.h2cube != nullptr)
		{

			if (o.h2cube->dx < -1.6)
			{
				o.h2cube->ddx = -o.h2cube->ddx;


			}
			else if (o.h2cube->dx > 0.0)
			{
				o.h2cube->ddx = -o.h2cube->ddx;

			}

			o.h2cube->dx += o.h2cube->ddx;
			printf("b : %f\n", o.h2cube->ddx);


			for (int i = 0; i < 4; i++)
			{
				o.h2cube->bot[i].x += o.h2cube->ddx;
				o.h2cube->top[i].x += o.h2cube->ddx;

			}
			printf("re : %f\n", o.h2cube->dx);




		}

	}

	glutPostRedisplay();
	glutTimerFunc(10, updateH2ObsTimer, NULL);
}
void updateVObsTimer(int unused)
{

	for (auto& o : obs)
	{
		if (o.vcube != nullptr)
		{

			if (o.vcube->dz < -1.8)
			{
				o.vcube->ddz = -o.vcube->ddz;


			}
			else if (o.vcube->dz > 0.0)
			{
				o.vcube->ddz = -o.vcube->ddz;

			}

			o.vcube->dz += o.vcube->ddz;
			printf("b : %f\n", o.vcube->ddz);


			for (int i = 0; i < 4; i++)
			{
				o.vcube->bot[i].z -= o.vcube->ddz;
				o.vcube->top[i].z -= o.vcube->ddz;

			}
			printf("re : %f\n", o.vcube->dz);




		}

	}

	glutPostRedisplay();
	glutTimerFunc(10, updateVObsTimer, NULL);
}
void updateV2ObsTimer(int unused)
{

	for (auto& o : obs)
	{
		if (o.vcube != nullptr)
		{

			if (h1dz < 0)
			{
				ddz = -ddz;
			}
			else if (h1dz > 1.0)
			{
				ddz = -ddz;

			}
			h1dz += ddz;



			for (int i = 0; i < 4; i++)
			{
				o.vcube->bot[i].z += ddz;
				o.vcube->top[i].z += ddz;
				

			}

			


		}

	}

	glutPostRedisplay();
	glutTimerFunc(10, updateVObsTimer, NULL);
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

//1 큐브 2 좌우 큐브 3 메이즈 큐브 4 상하 큐브 
//구조물 함수 최소거리2, 최대거리 3.2  
void cross_maze(float z)
{
	//파란 교차 구간
	{
		{
			Obstacles temp3(MageCube(glm::vec3(0.2, 0.1, z), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(0.0, 0.1, z), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z-0.5), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 0.5), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.5), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 0.5), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 0.5), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 0.5), 0.2));
			obs.push_back(temp3);
		}

		//아이템
		{
			Item temp(Heal(glm::vec3(-0.0, 0.1, z - 0.5), 0.05));
			item.push_back(temp);
		}



	}

}
void way_3(float z)
{
	
		//왼쪽
		{
			Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1,z), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-0.2), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-0.6 ), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-1.0 ), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-1.4 ), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-1.8 ), 0.2));
			obs.push_back(temp);
		}
		//오른쪽
		{
			Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z), 0.2));
			obs.push_back(temp3);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 0.2), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 0.6), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 1.0), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 1.4), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z - 1.8), 0.2));
			obs.push_back(temp);
		}

		//3차로 끝나는 지점
		{
			{
				Obstacles temp3(HCube(glm::vec3(-0.6, 0.2, -7.4), 0.2));
				obs.push_back(temp3);
			}

		}

	
}
void side_maze(float z)
{
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z), 0.2));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z-0.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 0.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 0.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.2), 0.2));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.4), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 0.4), 0.2));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 0.6), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 0.6), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 0.6), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.6), 0.2));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 0.8), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 0.8), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.8), 0.2));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 0.8), 0.2));
		obs.push_back(temp3);
	}



	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 1.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 1.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 1.2), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 1.2), 0.2));
		obs.push_back(temp3);
	}

	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 1.4), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 1.4), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 1.4), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 1.4), 0.2));
		obs.push_back(temp3);
	}


	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 1.8), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 1.8), 0.2));
		obs.push_back(temp3);
	}



	{
		Obstacles temp3(MageCube(glm::vec3(-0.8, 0.1, z - 2.0), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(-0.4, 0.1, z - 2.0), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.4, 0.1, z - 2.0), 0.2));
		obs.push_back(temp3);
	}
	{
		Obstacles temp3(MageCube(glm::vec3(0.8, 0.1, z - 2.0), 0.2));
		obs.push_back(temp3);
	}


	//상하
	{
		Obstacles temp4(VCube(glm::vec3(0.0, 0.1, z - 2.0), 0.2));
		obs.push_back(temp4);
	}

	//아이템
	{
		Item temp(Heal(glm::vec3(-0.8, 0.1, z-1.8), 0.05));
		item.push_back(temp);
	}










}
void zige(float z)
{
	{
				Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z), 0.2));
				obs.push_back(temp);
	}

	{
		{
		Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-0.4), 0.2));
		obs.push_back(temp);
		}

		{
		Obstacles temp(Cube(glm::vec3(0.8, 0.1, z-0.4), 0.2));
		obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z-0.8), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z-0.8), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z-1.2), 0.2));
			obs.push_back(temp);
		}
	}

	{

		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-1.6), 0.2));
			obs.push_back(temp);
		}

	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z-2.0), 0.2));
			obs.push_back(temp);
		}

	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z-2.4), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.4, 0.1, z-2.4), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z-2.8), 0.2));
			obs.push_back(temp);
		}
		{
			Obstacles temp(Cube(glm::vec3(0.8, 0.1, z-2.8), 0.2));
			obs.push_back(temp);
		}
	}

	{
		{
			Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z-3.2), 0.2));
			obs.push_back(temp);
		}
	}


	//아이템
	{
		Item temp(Heal(glm::vec3(-0.8, 0.1, z - 3.2), 0.05));
		item.push_back(temp);
	}
}
void asd(float z)
{
{
	Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z), 0.2));
	obs.push_back(temp);
}


{
	Obstacles temp(Cube(glm::vec3(-0.4, 0.1, z), 0.2));
	obs.push_back(temp);
}


{
	Obstacles temp(Cube(glm::vec3(-0.0, 0.1, z), 0.2));
	obs.push_back(temp);
}


{
	Obstacles temp(Cube(glm::vec3(0.4, 0.1, z), 0.2));
	obs.push_back(temp);
}


{
	Obstacles temp(Cube(glm::vec3(0.8, 0.1, z), 0.2));
	obs.push_back(temp);
}
}
void hzone(float z)
{ 
{
	Obstacles temp2(HCube(glm::vec3(-0.8, 0.1, z), 0.2));
	obs.push_back(temp2);
}

{
	Obstacles temp5(H2Cube(glm::vec3(0.8, 0.1, z - 0.4), 0.2));
	obs.push_back(temp5);
}
{
	Obstacles temp2(HCube(glm::vec3(-0.8, 0.1, z-0.8), 0.2));
	obs.push_back(temp2);
}

{
	Obstacles temp5(H2Cube(glm::vec3(0.8, 0.1, z - 1.2), 0.2));
	obs.push_back(temp5);
}



}


void debug()
{
	float z = -1;
	int pattern = 0;
	for (int i=0;i < 10;i++)
	{
		pattern = rand() % 5 ;
		if (pattern == 0)
		{
			hzone(z);
		}
		else if (pattern == 1)
		{
			way_3(z);
		}
		else if (pattern == 2)
		{
			side_maze(z);
		}
		else if (pattern == 3)
		{
			cross_maze(z);
		}
		else if (pattern == 4)
		{
			zige(z);
		}
		z -= 4;
		
		("%d\n", pattern);
	}
	
	//side_maze(z);
	//zige(z);
	
//	{
//	//입구
//	{
//		z = -1;
//		{
//			Obstacles temp(Cube(glm::vec3(-0.8, 0.1, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(0.8, 0.1, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(-0.8, 0.5, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(0.8, 0.5, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(-0.6, 0.9, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(0.6, 0.9, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(-0.2, 0.9, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(0.2, 0.9, z), 0.2));
//			obs.push_back(temp);
//		}
//		{
//			Obstacles temp(Cube(glm::vec3(-0.8, 0.5, z), 0.2));
//			obs.push_back(temp);
//		}
//
//	}
//
//
//	//cross_maze
//	{
//		z = -4;
//		cross_maze(z);
//
//	}
//
//	//way_3
//	{
//		z = -5.2;
//		way_3(z);
//	}
//
//
//	//상하 구간
//	{
//		z = -11;
//		side_maze(z);
//	}
//
//	//좌우 장애물
//	{
//		z = -2;
//		Obstacles temp3(HCube(glm::vec3(-0.6, 0.2, z), 0.1));
//		obs.push_back(temp3);
//	}
//	//상하 장애물
//	{
//		{
//			Obstacles temp2(MageCube(glm::vec3(-0.0, 0.1, -8.7), 0.2));
//			obs.push_back(temp2);
//		}
//		{
//			Obstacles temp4(VCube(glm::vec3(0.8, 0.1, -9.2), 0.2));
//			obs.push_back(temp4);
//		}
//
//
//
//
//
//	}
//}
}