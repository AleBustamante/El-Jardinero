#include "GameLoader.h"
#include "GameplayManager.h"
#include "SoundManager.h"
#include <iostream>


void moveSprite(typeSprite& sprite) {
	
	DrawTexture(sprite.texture, sprite.posX, sprite.posY, WHITE);
	sprite.posX += sprite.velocityX * velReducer;
	sprite.posY += sprite.velocityY * velReducer;
	
	//std::cout << sprite.velocityX * velReducer << '\t' << sprite.velocityY * velReducer << std::endl;
}

void drawFlowers(std::vector<typeSprite>& flowers, std::vector<typeSprite>& enemies) {
	for (int i = 0; i < flowers.size(); i++) {
		flowers[i].color = flowerLvlColor(flowers[i]);
		DrawTexture(flowers[i].texture, flowers[i].posX, flowers[i].posY, flowers[i].color);
	}
}


void spawnEnemies(std::vector<typeSprite>& enemies, typeSprite initValuesEnemy, int& currentScore) {
	if (spawnNewWave(currentScore)) {
		initValuesEnemy.posX = randomNumber(1, 960);
		enemies.push_back(initValuesEnemy);
	}
	for (int i = 1; i < enemies.size(); i++) {
		moveSprite(enemies[i]);
		if (enemies[i].posY > 640) {
			enemies.erase(enemies.begin());
		}
	}
}


void spawnProjectile(typeSprite protagonist, std::vector<typeSprite>& projectiles, Sound& soundEffect) {
	
	for (int i = 0; i < projectiles.size(); i++) {
		moveSprite(projectiles[i]);

		if (projectiles[i].posY < -5 || projectiles[i].posY > 1150) {
			projectiles.erase(projectiles.begin());
		}
	}
	
	
}

void spawnFertilizer(typeSprite protagonist, typeSprite& fertilizer, bool& activateFertilizer) {
	if (activateFertilizer && fertilizer.posY < 640) {
		moveSprite(fertilizer);
	}
	else {
		activateFertilizer = false;
		fertilizer.posY = outOfScreen;
	}
}

void updateFlower(std::vector<typeSprite>& flowers, typeSprite& fertilizer, bool& activateFertilizer) {
	for (int i = 0; i < flowers.size(); i++) {
		if (checkCollitionX(flowers[i], fertilizer) && checkCollitionY(flowers[i], fertilizer)) {
			if (activateFertilizer) {
				flowers[i].lvl++;
				flowers[i].color = flowerLvlColor(flowers[i]);
			}
			activateFertilizer = false;
		}
	}
}

float radToDegree(float radians) {
	int degrees;
	degrees = (radians * 180) / PI;
	return degrees;
}

float shootingAngle(typeSprite& protagonist) {
	Vector2 mousePos, deltaPos;
	float shootAngle;
	mousePos = GetMousePosition();
	deltaPos.x = (mousePos.x - protagonist.posX);
	deltaPos.y = (mousePos.y - protagonist.posY) ;
	shootAngle = atan2(deltaPos.y, deltaPos.x);
	//std::cout << shootAngle << std::endl;

	return shootAngle;
}


//Vector velocidad para la bala
Vector2 shootVector(typeSprite& protagonist) {
	Vector2 velocityVec;
	velocityVec.x = cos(shootingAngle(protagonist));
	velocityVec.y = sin(shootingAngle(protagonist));
	
	
	//std::cout << radToDegree( (shootingAngle(protagonist))) << '\t' << radToDegree( (shootingAngle(protagonist))) << std::endl;
	return velocityVec;
}