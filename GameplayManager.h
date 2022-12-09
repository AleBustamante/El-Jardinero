#pragma once

#include "raylib.h"
#include "SpriteManager.h"
#include <string>
#include <random>
#include <cmath>

constexpr int begginer = 10;
constexpr int intermidiate = 20;
constexpr int expert = 30;

constexpr int lvl1 = 100;
constexpr int lvl2 = 200;
constexpr int lvl3 = 300;


int randomNumber(int rangeBottom, int rangeTop);

int currentLvl(int& currentScore);

bool spawnNewWave(int& currentScore);

Color flowerLvlColor(typeSprite& flower);

void updateOnLvl(std::vector<typeSprite>& sprite1, std::vector<typeSprite>& sprite2, int sprite1Pos, int sprite2Pos);

void updateOnCollition(std::vector<typeSprite>& enemies, std::vector<typeSprite>& projectiles, bool& hitEnemy);

bool checkCollitionX(typeSprite& sprite1, typeSprite& sprite2);

bool checkCollitionY(typeSprite& sprite1, typeSprite& sprite2);

void generalUpdate(std::vector<typeSprite>& enemies, std::vector<typeSprite>& projectiles, std::vector<typeSprite>& flowers, int& currentScore);

void printScore(int& currentScore);


