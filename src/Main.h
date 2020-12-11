#pragma once
#include "FRAMEWORK/openGL.h"

// ESSENTIAL
GLvoid drawScene();
GLvoid reShape(int w, int h);

// CALLBACK FUNC
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void updateChrHpTimer(int unused);
void updateItemTimer(int unused);

// INI FUNC
void iniUniformData(GLuint pid);
void iniUniformData2(GLuint pid);
void iniKeyValues();