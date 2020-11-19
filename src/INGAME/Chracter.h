#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
#include "../FRAMEWORK/Camera.h"
#include "../Main.h"
#include <vector>

class Character
{
public:
	float x = 0, y = 0.16, z = 0, speed = 0.01; // ĳ���� ��ǥ, �̵��ӵ�
	float aAngle = 0, lAngle = 0, angle = 0;    // ��, �ٸ�, Ÿ�̸� ����

	void drawCharacter(Shader& s, Camera& c);
};

void chr_keyboard_event(Character& chr, Camera& c, unsigned char key, int x, int y);

void chr_set_camera_view_matrix(Character& chr, Camera& c, GLuint pid);
void chr_camera_mouse_motion_event(Character& chr, Camera& c, int x, int y);