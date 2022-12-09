#pragma once
#include <vector>
#include "raylib.h"


constexpr int lastRowY = 576;
constexpr int lastRowX = 0;
constexpr int outOfScreen = 1500;

constexpr int velZero = 0;
constexpr int posZero = 0;
constexpr int baseEnemyVel = 30;

constexpr int initPositionX = 900;
constexpr int initPositionY = 576;
constexpr int baseToolSpeed = 150;
constexpr int initPosPlayerX = 480;
constexpr int initPosPlayerY = 500;

constexpr float frameSpeed = 1 / 60;

constexpr float velReducer = 0.02;

typedef struct {
	float velocityX;
	float velocityY;
	Texture2D texture;
	float posX;
	float posY;
	int lvl;
	Color color;
	int sideLength;
} typeSprite;



void moveSprite(typeSprite& sprite);

void drawFlowers(std::vector<typeSprite>& flowers, std::vector<typeSprite>& enemies);

void spawnEnemies(std::vector<typeSprite>& enemies, typeSprite initValuesEnemy, int& currentScore);

void spawnProjectile(typeSprite protagonist, std::vector<typeSprite>& projectiles, Sound& soundEffect);

void spawnFertilizer(typeSprite protagonist, typeSprite& fertilizer, bool& activateFertilizer);

void updateFlower(std::vector<typeSprite>& flowers, typeSprite& fertilizer, bool& activateFertilizer);

float radToDegree(float radians);

float shootingAngle(typeSprite& protagonist);

Vector2 shootVector(typeSprite& protagonist);
