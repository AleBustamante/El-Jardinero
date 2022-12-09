#include <iostream>
#include "InputHandler.h"
#include "GameLoader.h"
#include "GameplayManager.h"
#include "SoundManager.h"


int main()
{
	InitWindow(960, 630, "El jardinero");
	
	SetWindowState(FLAG_VSYNC_HINT);
	//Crea struct y llama a función para inicializar variables desde el main
	//--------------------------------------------------------
	typeMainVar mainVar;
	loadMainVariables(mainVar);
	//--------------------------------------------------------


	while (!WindowShouldClose()) {
		BeginDrawing();
		
		//Condicional para menú principal
		//----------------------------
		if (gameStarted(mainVar.showMenu) && !mainVar.hasName) {
			drawMenu(mainVar, menuText);
		}
		//----------------------------

		//Condicional para input de nombre
		//-----------------------------------
		else if (!gameStarted(mainVar.showMenu) && !mainVar.hasName) {
			DrawTexture(mainVar.textureList[menuText], 0, 0, DARKGREEN);
			DrawText("Ingrese su nombre:", 250, 300, 40, BLACK);
			inputTextToScreen(mainVar);
		}
		//-----------------------------------

		//Ciclo principal del juego
		//-----------------------------------
		else if (!mainVar.isPaused && !hasPlayerLost(mainVar.enemies)) {
			
			ClearBackground(WHITE);
			
	
			//Dibuja y controla: mapa, flores, herramienta, fertilizante
			//---------------------------------------------
			drawMap(mainVar.textureList);
			drawFlowers(mainVar.flowers, mainVar.enemies);
			moveSprite(mainVar.protagonist);
			checkInput(mainVar);

			spawnFertilizer(mainVar.protagonist, mainVar.fertilizer, mainVar.activateFertilizer);
			//---------------------------------------------


			//Spawnea enemigos y proyectiles
			//---------------------------------------------
			spawnEnemies(mainVar.enemies, mainVar.initValEnemy, mainVar.currentScore);
			spawnProjectile(mainVar.protagonist, mainVar.projectiles, mainVar.soundList[0]);
			//---------------------------------------------


			//Actualiza todas las colisiones del mapa (incluyendo fertilizante en flor)
			//--------------------------------------------------------------------------
			generalUpdate(mainVar.enemies, mainVar.projectiles, mainVar.flowers, mainVar.currentScore);
			printScore(mainVar.currentScore);
			updateFlower(mainVar.flowers, mainVar.fertilizer, mainVar.activateFertilizer);
			//--------------------------------------------------------------------------

			DrawFPS(930, 10);
		}
		//-----------------------------------

		//Menú de pausa
		//-----------------------------------
		else if (mainVar.isPaused == true) {
			drawMenu(mainVar, PauseText);
		}
		//-----------------------------------

		//Pantalla final
		//-----------------------------------
		else if (hasPlayerLost(mainVar.enemies)) {
			drawEndScreen(mainVar);
		}
		//-----------------------------------
		EndDrawing();
	}
	saveGame(mainVar);


	CloseAudioDevice();
	unloadAllTextures(mainVar.textureList);
	CloseWindow();
	return 0;
}
