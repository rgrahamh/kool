#include "headers/Object.hpp"
#include "headers/Globals.hpp"
#include "headers/Sprite.hpp"
#include <iostream>

#define Keys sf::Keyboard

using namespace std;

std::vector<Sprite *>spriteIndex = std::vector<Sprite *>();

Object::Object(int x, int y){
	this->x = (float)x;
	this->y = (float)y;
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
void Object::decHitBoxes(double delta){

	return;
}

//Engine-defined process function
void Object::_process(double delta){
    this->process(delta);
	decHitBoxes(1.0);
}

//Developer-defined virtual function
void Object::process(double delta){
    if(Keys::isKeyPressed(Keys::D)){
        x += 5 * delta;
    }
    if(Keys::isKeyPressed(Keys::A)){
        x -= 5 * delta;
    }
    if(Keys::isKeyPressed(Keys::W)){
        y -= 5 * delta;
    }
    if(Keys::isKeyPressed(Keys::S)){
        y += 5 * delta;
    }
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

