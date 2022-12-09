#pragma once

#include "TextureManager.h"
#include "SpriteManager.h"
#include <vector>
#include <fstream>
#include <string>


typedef struct {
	Texture2D textureList[20];
	Sound soundList[20];
	int currentScore;
	typeSprite protagonist;
	typeSprite initValProtagonist;
	typeSprite fertilizer;
	bool activateFertilizer;
	std::vector<typeSprite> projectiles;
	typeSprite initValProjectile;
	std::vector<typeSprite> enemies;
	typeSprite initValEnemy;
	std::vector<typeSprite> flowers;
	typeSprite initValFlower;
	char playerName[20];
	bool hasName;
	bool isPaused;
	bool showMenu;
	int optionSelected;
	float currentMenuPosition;
	bool endScreenShown;
}typeMainVar;

typedef struct {
	char name[20];
	int score;
}typeHighScore;

constexpr int tileSpace = 32;



void loadMainVariables(typeMainVar& variable);

void startNewGame(typeMainVar& mainVariables);

void drawMap(Texture2D textureList[]);

bool gameStarted(bool& hasSelected);

void drawMenu(typeMainVar& mainVariables, int textureBackground);



void drawEndScreen(typeMainVar& mainVariables);

void drawLeaderboard(typeMainVar& mainVariables);

void arrayToArray(char ogArray[], char copyArray[]);

void orderScores(typeMainVar& mainVariables);

void stringToArray(std::string textString, char textChar[]);

void saveGame(typeMainVar& mainVariables);

void loadGame(typeMainVar& mainVariables);

void clearGameData(typeMainVar& mainVariables);


void saveScore(typeMainVar& mainVar);

bool hasPlayerLost(std::vector<typeSprite>& enemies);

void checkGameStatus(typeMainVar mainVariables);
