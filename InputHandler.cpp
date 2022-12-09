#include "InputHandler.h"
#include "GameplayManager.h"
#include "GameLoader.h"
#include "SoundManager.h"
#include <iostream>


void checkInput(typeMainVar& mainVariables) {
	int keyPressed = -1;
	
	//if (IsGamepadButtonDown()) {
		//keyPressed = KEY_DOWN;
	//}

	if (IsKeyDown(KEY_W)) {
		keyPressed = KEY_W;
	}
	if (IsKeyDown(KEY_S)) {
		keyPressed = KEY_S;
	}
	if (IsKeyDown(KEY_A)) {
		keyPressed = KEY_A;
	}
	if (IsKeyDown(KEY_D)) {
		keyPressed = KEY_D;
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		keyPressed = MOUSE_BUTTON_LEFT;
		
	}
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		keyPressed = MOUSE_BUTTON_RIGHT;
	}
	if (IsKeyPressed(KEY_L)) {
		keyPressed = KEY_L;
	}

	if (IsKeyPressed(KEY_TAB)) {
		keyPressed = KEY_TAB;
	}

	if (IsKeyPressed(KEY_ESCAPE)) {
		keyPressed = KEY_ESCAPE;
	}



	switch (keyPressed)
	{
	case KEY_W:
		mainVariables.protagonist.velocityY = -200;
		moveSprite(mainVariables.protagonist);
		break;
	case KEY_S:
		mainVariables.protagonist.velocityY = 250;
		moveSprite(mainVariables.protagonist);
		break;
	case KEY_A:
		mainVariables.protagonist.velocityX = -200;
		moveSprite(mainVariables.protagonist);
		break;
	case KEY_D:
		mainVariables.protagonist.velocityX = 250;
		moveSprite(mainVariables.protagonist);
		break;
	case MOUSE_BUTTON_LEFT:

		//playSounds(soundEffect[0]);
		Vector2 velocityVect = shootVector(mainVariables.protagonist);
		mainVariables.initValProjectile = { 500, 500, mainVariables.textureList[projectileText], posZero, posZero, 1, WHITE, 16 }; //Reinicia valor de proyectil
		mainVariables.initValProjectile.posX = mainVariables.protagonist.posX;
		mainVariables.initValProjectile.posY = mainVariables.protagonist.posY;
		mainVariables.initValProjectile.velocityY *= velocityVect.y;
		mainVariables.initValProjectile.velocityX *= velocityVect.x;
		mainVariables.projectiles.push_back(mainVariables.initValProjectile);
		//std::cout << mainVariables.initValProjectile.velocityX << '\t' << mainVariables.initValProjectile.velocityY << std::endl;
		break;
	case MOUSE_BUTTON_RIGHT:
		if (!mainVariables.activateFertilizer) {
			mainVariables.activateFertilizer = true;
			mainVariables.fertilizer.posX = mainVariables.protagonist.posX;
			mainVariables.fertilizer.posY = mainVariables.protagonist.posY;
			mainVariables.fertilizer.velocityY = 100;
			mainVariables.fertilizer.velocityX = 0;
		}
		break;
	case KEY_ESCAPE:
		mainVariables.isPaused = true;
		break;
	case KEY_TAB:
		loadGame(mainVariables);
		break;
	default:
		break;
	}
	mainVariables.protagonist.velocityY = 0;
	mainVariables.protagonist.velocityX = 0;
}


void checkMenuInput(typeMainVar& mainVariables) {
	int keyPressed = 0;
	if (IsKeyDown(KEY_UP)) {
		keyPressed = KEY_UP;
	}
	if (IsKeyDown(KEY_DOWN)) {
		keyPressed = KEY_DOWN;
	}
	if (IsKeyPressed(KEY_ENTER)) {
		keyPressed = KEY_ENTER;
	}
	if (IsKeyPressed(KEY_ESCAPE)) {
		keyPressed = KEY_ESCAPE;
	}
	if (IsKeyPressed(KEY_ESCAPE)) {
		keyPressed = KEY_ESCAPE;
	}

	switch (keyPressed)
	{
	case KEY_UP:
		mainVariables.currentMenuPosition -= 0.1;
		if (mainVariables.currentMenuPosition < 0) {
			mainVariables.currentMenuPosition = 3;
		}
		//std::cout << posReference << std::endl;
		break;
	case KEY_DOWN:
		mainVariables.currentMenuPosition += 0.1;
		if (mainVariables.currentMenuPosition > 3) {
			mainVariables.currentMenuPosition = 0;
		}
		//std::cout << posReference << std::endl;
		break;
	case KEY_ENTER:
		mainVariables.optionSelected = mainVariables.currentMenuPosition;
		break;
	case KEY_ESCAPE:
		mainVariables.isPaused = false;
		SetExitKey(KEY_F1);
		mainVariables.optionSelected = -1;
		break;
	default:
		int optionSelected = (int)mainVariables.currentMenuPosition;
		mainVariables.currentMenuPosition = optionSelected + 0.5;
		break;
	}
}


void inputTextToScreen(typeMainVar& mainVariables) {
	int namePos = strlen(mainVariables.playerName);
	if (IsKeyPressed(KEY_BACKSPACE)) {
		mainVariables.playerName[namePos - 1] = '\0';
	}
	else if(!IsKeyPressed(KEY_ENTER)) {
		mainVariables.playerName[namePos] = GetKeyPressed();
		mainVariables.playerName[namePos + 1] = '\0';
		DrawText(mainVariables.playerName, 250, 400, 20, WHITE);
	}
	if (IsKeyPressed(KEY_ENTER)) {
		mainVariables.hasName = true;
	}
}
