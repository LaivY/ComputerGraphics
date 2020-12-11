#pragma once
#include "../FRAMEWORK/openGL.h"
#include "../FRAMEWORK/Shader.h"
#include "Chracter.h"
#include <vector>

void drawLand(Shader& s);
void drawMap(Shader& s, Camera& c, std::vector<Obstacles>& obs, Character& chr);
void drawMiniMab(Shader& s, Camera& c, std::vector<Obstacles>& obs, Character& chr);
void drawMiniMabEdge(Shader& s);
void drawMiniMabBGR(Shader& s);
void drawHPBar(Shader& s, int hp);
void drawHPBarEdge(Shader& s);