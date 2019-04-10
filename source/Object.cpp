#include "headers/Object.hpp"
#include "headers/Globals.hpp"
#include "headers/Sprite.hpp"
#include <iostream>

using namespace std;

std::vector<Sprite *>spriteIndex = std::vector<Sprite *>();

Object::Object(int x, int y){
	this->x = x;
	this->y = y;
	this->sprite = NULL;
	this->imageIndex = -1;
	this->create();
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

//Decrement hit box counters
void Object::decHitBoxes(float delta){

	return;
}

//Engine-defined process function
void Object::_process(){
	
    	this->process();
	decHitBoxes(1.0);
}

//Developer-defined virtual function
void Object::process(){
	return;
}

//Developer-defined virtual function
void Object::onCollide(Object *other, int myBoxID, int otherBoxID){
	return;
}

//Developer defined virtual function
void Object::create(){
	return;
}

void Object::setSprite(Sprite *sprite){
	this->sprite = sprite;
	this->imageIndex = 0;
}

void Object::setSprite(unsigned int index){
	if(index < spriteIndex.size()){
		this->sprite = spriteIndex[index];
		this->imageIndex = 0;
	}
}

