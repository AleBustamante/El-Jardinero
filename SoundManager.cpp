#include "SoundManager.h"

void loadAllSounds(Sound soundList[]){
	soundList[shootSound] = LoadSound("C:/Users/Alejandro/Documents/Universidad/Proyectos Progra/El Jardinero/assets/sound/shoot.mp3");
}

void playSounds(Sound& soundEffect) {
	PlaySound(soundEffect);
}
