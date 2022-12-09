#include "GameLoader.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include <vector>
#include <fstream>
#include <iostream>


int map[20][30] = {{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
					{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
					{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4},
					{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4}};



void loadMainVariables(typeMainVar& mainVar) {
	InitAudioDevice();
	loadAllTextures(mainVar.textureList);
	loadAllSounds(mainVar.soundList);

	SetExitKey(KEY_F1);

	mainVar.protagonist = {velZero, velZero, mainVar.textureList[toolText], initPosPlayerX, initPosPlayerY, 1, WHITE, 16};


	mainVar.initValFlower = { velZero, velZero, mainVar.textureList[flowerText], initPositionX, initPositionY, 1, WHITE, 32};
	for (int i = 0; i < 15; i++) {
		mainVar.flowers.push_back(mainVar.initValFlower);
		mainVar.initValFlower.posX += 64;
	}

	mainVar.initValProjectile = { 1000, 1000, mainVar.textureList[projectileText], posZero, posZero, 1, WHITE, 16};
	mainVar.initValEnemy = { velZero, 100, mainVar.textureList[enemyText], posZero, posZero, 1, WHITE, 16};
	

	mainVar.fertilizer.texture = mainVar.textureList[fertilizerText];
	mainVar.fertilizer.sideLength = 1;
	mainVar.activateFertilizer = false;

	mainVar.currentScore = 0;

	mainVar.playerName[0] = '\0';
	mainVar.hasName = false;
	

	mainVar.optionSelected = -1;
	mainVar.currentMenuPosition = 0;

	mainVar.showMenu = true;
	mainVar.isPaused = true;
	mainVar.endScreenShown = false;
}

void startNewGame(typeMainVar& mainVariables) {
		clearGameData(mainVariables);
		mainVariables.initValFlower.posX = 0;
		for (int i = 0; i < 15; i++) {
			mainVariables.flowers.push_back(mainVariables.initValFlower);
			mainVariables.initValFlower.posX += 64;
		}
		mainVariables.protagonist.posX = initPositionX;
		mainVariables.protagonist.posX = initPositionY;
}

void drawMap(Texture2D textureList[]) {
	int posX = 0;
	int posY = 0;
	for (int f = 0; f < 20; f++) {
		for (int c = 0; c < 30; c++) {
			DrawTexture(textureList[map[f][c]], posX * tileSpace, posY * tileSpace, WHITE);
			posX++;
		}
		posY++;
		posX = 0;
	}
}

bool gameStarted(bool& hasSelected) {
	bool exitMenu = false;
	if (hasSelected) {
		exitMenu = true;
	}
	return exitMenu;
}


void drawMenu(typeMainVar& mainVariables, int menuBackground) {

	checkMenuInput(mainVariables);

	DrawTexture(mainVariables.textureList[menuBackground], 0, 0, WHITE);

	if (mainVariables.currentMenuPosition >= 0 && mainVariables.currentMenuPosition < 1 && mainVariables.optionSelected == -1) {
		DrawText("Nuevo Juego", 350, 450, 20, BLUE);
		DrawText("Cargar Juego", 350, 500, 20, WHITE);
		DrawText("Salir", 350, 550, 20, WHITE);
	}
	else if (mainVariables.currentMenuPosition >= 1 && mainVariables.currentMenuPosition < 2 && mainVariables.optionSelected == -1) {
		DrawText("Nuevo Juego", 350, 450, 20, WHITE);
		DrawText("Cargar Juego", 350, 500, 20, BLUE);
		DrawText("Salir", 350, 550, 20, WHITE);
	}
	else if (mainVariables.currentMenuPosition >= 2 && mainVariables.currentMenuPosition <3 && mainVariables.optionSelected == -1) {
		DrawText("Nuevo Juego", 350, 450, 20, WHITE);
		DrawText("Cargar Juego", 350, 500, 20, WHITE);
		DrawText("Salir", 350, 550, 20, BLUE);
	}
	switch (mainVariables.optionSelected) {
		case 0:
			startNewGame(mainVariables);
			mainVariables.showMenu = false;
			mainVariables.isPaused = false;
			mainVariables.optionSelected = -1;
			break;
	
		case 1:
			loadGame(mainVariables);
			mainVariables.showMenu = false;
			mainVariables.isPaused = false;
			mainVariables.hasName = true;
			mainVariables.optionSelected = -1;
			break;

		case 2:
			drawMap(mainVariables.textureList);
			DrawText("Presiona ENTER para confirmar que quieres salir", 200, 50, 20, WHITE);
			DrawText("Todo tu progreso sera guardado", 250, 100, 20, WHITE);
			SetExitKey(KEY_ENTER);
			if (IsKeyPressed(KEY_ESCAPE)) {
				SetExitKey(KEY_F1);
			}
			break;
	}
}


void drawEndScreen(typeMainVar& mainVariables) {
	drawMap(mainVariables.textureList);
	if (!mainVariables.endScreenShown) {
		DrawText("PERDISTE", 100, GetScreenHeight() / 3, 150, RED);
		DrawText("Presiona ENTER para regresar al menu principal", 90, 400, 30, RED);
		char playerNameScore[150];
		char score[4];
		_itoa_s(mainVariables.currentScore, score, 4, 10);
		strcpy_s(playerNameScore, mainVariables.playerName);
		strcat_s(playerNameScore, ", tu puntuacion fue de ");
		strcat_s(playerNameScore, score);

		DrawText(playerNameScore, 30, 20, 40, DARKBLUE);
		
	}
	if (IsKeyPressed(KEY_ENTER)) {
		mainVariables.hasName = false;
		mainVariables.showMenu = true;
	}
}



void stringToArray(std::string textString, char textChar[]) {
	int i = 0;
	for (; i < textString.size(); i++) {
		textChar[i] = textString[i];
	}
	textChar[i] = '\0';
}


void saveGame(typeMainVar& mainVariables){
	std::ofstream saveEnem;
	std::ofstream saveProj;
	std::ofstream saveFlow;
	std::ofstream saveScore;
	std::ofstream saveName;

	saveEnem.open("./saved games/saveEnem.dat", std::ios::binary);
	for (int i = 0; i < mainVariables.enemies.size(); i++) {
		saveEnem.write((char*)&mainVariables.enemies[i], sizeof(mainVariables.enemies[i]));
	}

	saveProj.open("./saved games/saveProj.dat", std::ios::binary);
	for (int i = 0; i < mainVariables.projectiles.size(); i++) {
		saveProj.write((char*)&mainVariables.projectiles[i], sizeof(mainVariables.projectiles[i]));
	}

	saveFlow.open("./saved games/saveFlow.dat", std::ios::binary);
	for (int i = 0; i < mainVariables.flowers.size(); i++) {
		saveFlow.write((char*)& mainVariables.flowers[i], sizeof(mainVariables.flowers[i]));
	}

	saveScore.open("./saved games/saveScore.dat", std::ios::binary);
	saveScore.write((char*)& mainVariables.currentScore, sizeof(mainVariables.currentScore));


	saveName.open("./saved games/saveName.dat", std::ios::binary);
	saveName.write((char*)&mainVariables.playerName, sizeof(mainVariables.playerName));

	saveEnem.close();
	saveProj.close();
	saveFlow.close();
	saveScore.close();
	saveName.close();
}


void loadGame(typeMainVar& mainVariables) {
	clearGameData(mainVariables);

	std::ifstream saveEnem;
	std::ifstream saveProj;
	std::ifstream saveFlow;
	std::ifstream saveScore;
	std::ifstream saveName;
	
	typeSprite tempEnemy;
	typeSprite tempProjectile;
	typeSprite tempFlower;

	saveEnem.open("./saved games/saveEnem.dat", std::ios::binary);
	while (!saveEnem.eof()) {
		saveEnem.read((char*)& tempEnemy, sizeof(tempEnemy));
		mainVariables.enemies.push_back(tempEnemy);

	}

	saveProj.open("./saved games/saveProj.dat", std::ios::binary);
	while(!saveProj.eof()) {
		saveProj.read((char*)& tempProjectile, sizeof(tempProjectile));
		mainVariables.projectiles.push_back(tempProjectile);

	}

	saveFlow.open("./saved games/saveFlow.dat", std::ios::binary);
	while (!saveFlow.eof()) {
		saveFlow.read((char*)& tempFlower, sizeof(tempFlower));
		mainVariables.flowers.push_back(tempFlower);
	}

	saveScore.open("./saved games/saveScore.dat", std::ios::binary);
	saveScore.read((char*)&mainVariables.currentScore, sizeof(mainVariables.currentScore));

	

	saveName.open("./saved games/saveName.dat", std::ios::binary);
	saveName.read((char*)&mainVariables.playerName, 20);

	saveEnem.close();
	saveProj.close();
	saveScore.close();
	saveName.close();
}

void clearGameData(typeMainVar& mainVariables) {
	mainVariables.enemies.erase(mainVariables.enemies.begin(), mainVariables.enemies.end());
	mainVariables.projectiles.erase(mainVariables.projectiles.begin(), mainVariables.projectiles.end());
	mainVariables.flowers.erase(mainVariables.flowers.begin(), mainVariables.flowers.end());
	mainVariables.currentScore = 0;
	mainVariables.endScreenShown = false;

}


bool hasPlayerLost(std::vector<typeSprite>& enemies) {
	bool hasLost = false;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i].posY > GetScreenHeight()) {
			hasLost = true;
		}
	}
	return hasLost;
}

void checkGameStatus(typeMainVar mainVariables) {
	if (hasPlayerLost(mainVariables.enemies)) {
		DrawTexture(mainVariables.textureList[PauseText], 0, 0, WHITE);
	}
}


/*void saveScore(typeMainVar& mainVar) {
	std::fstream leaderboard;
	
	std::string names[5];
	int scores[5];

	int leadPos = -1;
	int i = 0;

	leaderboard.open("./saved games/leaderboard.txt");

	leaderboard >> names[i];
	leaderboard >> scores[i];
	i++;
	while (!leaderboard.eof()) {
		if (mainVar.currentScore >= scores[i]) {
			leadPos = i;
		}
		leaderboard >> names[i];
		leaderboard >> scores[i];
	}
	leaderboard.seekg(std::ios::beg);
	if (leadPos != -1) {
		int j = 5;
		for (; j < leadPos; j--) {
			names[j] = names[j - 1];
			scores[j] = scores[j - 1];
	}
	names[j] = mainVar.playerName





	int k = 0;
	for (; k < strlen(mainVar.playerName); k++) {
		leaderboard << mainVar.playerName[k];
	}
	leaderboard << '\t';
	leaderboard << mainVar.currentScore;
	leaderboard << '\n';

	leaderboard.close();

}*/

