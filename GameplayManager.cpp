#include "GameplayManager.h"
#include <iostream>


int randomNumber(int rangeBottom, int rangeTop) {
    std::random_device random; // obtain a random number from hardware
    std::mt19937 generator(random()); // seed the generator
    std::uniform_int_distribution<> range(rangeBottom, rangeTop); // define the range

    return range(generator);
}


int currentLvl(int& currentScore)
{
    int difficulty = 1;
    if (currentScore < begginer) {
        difficulty = lvl1;
    }
    else if (currentScore < intermidiate) {
        difficulty = lvl2;
    }
    else if (currentScore < expert) {
        difficulty = lvl3;
    }
    else {
        difficulty = lvl3;
    }
    return difficulty;
}


bool spawnNewWave(int& currentScore) {
    if (randomNumber(1, 10000) <= currentLvl(currentScore)) {
        return true;
    }
    else {
        return false;
    }
}

Color flowerLvlColor(typeSprite& flower) {
    Color flowerColor = WHITE;
    switch (flower.lvl)
    {
    case 1:
        flower.color = WHITE;
        break;
    case 2:
        flowerColor = BLUE;
        break;
    case 3:
        flowerColor = RED;
        break;
    case 4:
        flowerColor = YELLOW;
        break;
    default:
        flowerColor = flower.color;
        break;
    }
    return flowerColor;
}

void updateOnLvl(std::vector<typeSprite>& sprite1, std::vector<typeSprite>& sprite2, int sprite1Pos, int sprite2Pos) {
    if (sprite1[sprite1Pos].lvl == sprite2[sprite2Pos].lvl) {
        sprite1.erase(sprite1.begin() + sprite1Pos);
        sprite2.erase(sprite2.begin() + sprite2Pos);
    }
    else if (sprite1[sprite1Pos].lvl > sprite2[sprite2Pos].lvl) {
        sprite2.erase(sprite2.begin() + sprite2Pos);
        sprite1[sprite1Pos].lvl--;
    }
    else if (sprite1[sprite1Pos].lvl < sprite2[sprite2Pos].lvl) {
        sprite1.erase(sprite1.begin() + sprite1Pos);
        sprite2[sprite2Pos].lvl--;
    }
}

void updateOnCollition(std::vector<typeSprite>& sprite1, std::vector<typeSprite>& sprite2, bool& collition) {
    for (int i = 0; i < sprite1.size(); i++) { //revisar valor de inicializacion de e
        for (int j = 0; j < sprite2.size(); j++) {
            if (i < sprite1.size() && j < sprite2.size()) {

                if (checkCollitionX(sprite1[i], sprite2[j] ) &&
                    checkCollitionY(sprite1[i], sprite2[j])) {
                    updateOnLvl(sprite1, sprite2, i, j);
                    collition = true;  
                }
            }
        }
    }
}

bool checkCollitionX(typeSprite& sprite1, typeSprite& sprite2) {
    bool collition = false;
    if ((sprite2.posX - sprite2.sideLength > sprite1.posX - sprite1.sideLength &&
        sprite2.posX - sprite2.sideLength < sprite1.posX + sprite1.sideLength) ||
        (sprite2.posX + sprite2.sideLength < sprite1.posX + sprite1.sideLength &&
         sprite2.posX + sprite2.sideLength > sprite1.posX - sprite1.sideLength) ||
        (sprite2.posX - sprite2.sideLength < sprite1.posX - sprite1.sideLength &&
         sprite2.posX + sprite2.sideLength > sprite1.posX + sprite1.sideLength)) {

        collition = true;
    }
    return collition;
}

bool checkCollitionY(typeSprite& sprite1, typeSprite& sprite2) {
    bool collition = false;
    if ((sprite2.posY - sprite2.sideLength > sprite1.posY - sprite1.sideLength &&
        sprite2.posY - sprite2.sideLength < sprite1.posY + sprite1.sideLength) ||
        (sprite2.posY + sprite2.sideLength < sprite1.posY + sprite1.sideLength &&
         sprite2.posY + sprite2.sideLength > sprite1.posY - sprite1.sideLength) ||
        (sprite2.posY - sprite2.sideLength < sprite1.posY - sprite1.sideLength &&
         sprite2.posY + sprite2.sideLength > sprite1.posY + sprite1.sideLength)) {

        collition = true;
    }
    return collition;
}


void generalUpdate(std::vector<typeSprite>& enemies, std::vector<typeSprite>& projectiles, std::vector<typeSprite>& flowers, int& currentScore) {
    bool hitEnemy = false;
    bool hitFlower = false;

    updateOnCollition(enemies, projectiles, hitEnemy);
    updateOnCollition(enemies, flowers, hitFlower);
    if (hitEnemy) {
        currentScore++;
    }
}


void printScore(int& currentScore) {

    char textScore[5];
    _itoa_s(currentScore, textScore, 5, 10);
    DrawText("PUNTAJE:", 800, 100, 25, WHITE);
    DrawText(textScore, 850, 120, 25, BLUE);
}



