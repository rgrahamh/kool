#include "headers/Object.hpp"

Object::Object(int x, int y){
	this->x = x;
	this->y = y;
	this->sprite = NULL;
}

struct drawData Object::_draw(){
	struct drawData data;

	data.x = this->x;
	data.y = this->y;
	if(this->sprite!=NULL){
		data.imageIndex = this->imageIndex; 	
	}else{
		data.imageIndex = -1;
	}
	data.sprite = this->sprite;

	return data;
}

void Object::process(){
	return;
}

void Object::onCollide(Object *other, int myBoxID, int otherBoxID){
	return;
}

void Object::create(){
	return;
}
