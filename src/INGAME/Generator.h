#pragma once
#include "../INGAME/Obstacle.h"
#include "../INGAME/Item.h"
#include <time.h>

void cross_maze(std::vector<Obstacles>& obs, float z);
void way_3(std::vector<Obstacles>& obs, float z);
void side_maze(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);
void zige(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);
void hzone(std::vector<Obstacles>& obs, float z);
void jump_1(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);
void jump_2(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);
void jump_3(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);
void genStructure(std::vector<Obstacles>& obs, std::vector<Item>& item, float z);