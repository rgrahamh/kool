#include "headers/Globals.hpp"
#include <iostream>

#define Keys sf::Keyboard
void basicMove(float *x, float *y, int speed, double delta){

	delta = delta / 10;

	if(Keys::isKeyPressed(Keys::D)){
        *x += speed * delta;
    }
    if(Keys::isKeyPressed(Keys::A)){
        *x -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::W)){
        *y -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::S)){
        *y += speed * delta;
    }
}

void createObject(Object *obj){
	if(activeEngine!=NULL){
		activeEngine->addObject(obj);
	}
	return;
}

bool setActiveScene(int sceneID){

	return activeEngine->setActiveScene(sceneID);
}

void playSound(char *filename, irrklang::ISoundEngine *engine, bool loop=false) {
    engine->play2D(filename, loop);
}

void stopAllSounds(irrklang::ISoundEngine *engine) {
    engine->stopAllSounds();
}