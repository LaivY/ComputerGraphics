#pragma once
#include "openGL.h"

// ESSENTIAL
GLvoid drawScene();
GLvoid reShape(int w, int h);

// CALLBACK FUNC
void motion(int x, int y);
void keyboard(unsigned char key, int x, int y);

// DRAW FUNC
void drawAxis();
void drawCube();

// INI FUNC
void iniUniformData(GLuint pid);