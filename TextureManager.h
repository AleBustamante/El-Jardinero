#pragma once
#include "raylib.h"


constexpr int enemyText = 0;
constexpr int toolText = 1;
constexpr int PauseText = 2;
constexpr int flowerText = 3;
constexpr int grassText = 4;
constexpr int dirtText = 5;
constexpr int skyText = 6;
constexpr int projectileText = 7;
constexpr int fertilizerText = 8;
constexpr int menuText = 9;


void loadAllTextures(Texture2D textureList[]);

void unloadAllTextures(Texture2D textureList[]);


