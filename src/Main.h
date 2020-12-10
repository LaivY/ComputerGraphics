#pragma once
#include "FRAMEWORK/openGL.h"

// ESSENTIAL
GLvoid drawScene();
GLvoid reShape(int w, int h);

void drawLand(GLuint pid);

// CALLBACK FUNC
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);

// INI FUNC
void iniUniformData(GLuint pid);