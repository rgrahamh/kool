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

int getSceneWidth(int sceneID){
    if(activeEngine!=NULL){
	    int width;
	    Scene *scene = activeEngine->getScene(sceneID);
	    if(scene!=NULL){
		    width = scene->width;
	    }else{
		    width = -1;
	    }
	    return width;
	}else{
		return -1;
	}
}
int getSceneHeight(int sceneID){
    if(activeEngine!=NULL){
	    int height;
	    Scene *scene = activeEngine->getScene(sceneID);
	    if(scene!=NULL){
		    height = scene->height;
	    }else{
		    height = -1;
	    }
	    return height;
	}else{
		return -1;
	}
}
