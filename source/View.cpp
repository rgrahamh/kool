#include "headers/View.hpp"

View::View(int winX, int winY, int sceneX, int sceneY, int width, int height){
	this->windowX = winX;
	this->windowY = winY;
	this->sceneX = sceneX;
	this->sceneY = sceneY;
	this->width = width;
	this->height = height;
	this->following = NULL;

}


struct position View::translate(int x, int y){ //NEEDS TESTING
	struct position newPos;

	newPos.x = (x + sceneX) + windowX;
	newPos.y = (y - sceneY) + windowY;

	return newPos;

}

void View::_process(){ //FIXME
	return;
}

void View::follow(){ //FIXME
	if(this->following==NULL){
		return;
	}else{
		return; 
	}
}
