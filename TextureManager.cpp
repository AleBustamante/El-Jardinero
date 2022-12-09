#include "TextureManager.h"
#include <string>
#include <iostream>


void loadAllTextures(Texture2D textureList[]) {
	textureList[enemyText] = LoadTexture("./assets/enemigo.png");
	textureList[toolText] = LoadTexture("./assets/herramienta.png");
	textureList[PauseText] = LoadTexture("./assets/pause.png");
	textureList[flowerText] = LoadTexture("./assets/flor.png");
	textureList[grassText] = LoadTexture("./assets/pasto.png");
	textureList[dirtText] = LoadTexture("./assets/tierra.png");
	textureList[skyText] = LoadTexture("./assets/cielo.png");
	textureList[projectileText] = LoadTexture("./assets/proyectil.png");
	textureList[fertilizerText] = LoadTexture("./assets/abono.png");
	textureList[menuText] = LoadTexture("./assets/menu.png");
	
}
void unloadAllTextures(Texture2D textureList[]) {
	UnloadTexture(textureList[0]);
	UnloadTexture(textureList[1]);
	UnloadTexture(textureList[2]);
	UnloadTexture(textureList[3]);
	UnloadTexture(textureList[4]);
	UnloadTexture(textureList[5]);
	UnloadTexture(textureList[6]);
	UnloadTexture(textureList[7]);
	UnloadTexture(textureList[8]);
	UnloadTexture(textureList[9]);
}
