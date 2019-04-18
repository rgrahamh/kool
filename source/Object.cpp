#include "headers/Object.hpp"
#include "headers/Sprite.hpp"
#include "headers/Globals.hpp"
#include <iostream>

#define Keys sf::Keyboard

using namespace std;

std::vector<Sprite *>spriteIndex = std::vector<Sprite *>();

Object::Object(float x, float y){
	this->x = x;
	this->y = y;
	this->sprite = NULL;
	this->imageIndex = -1;
	this->create();
	this->debug = false;
	this->collisionLayer = 0;
}

Object::Object(float x, float y, Sprite *sprite, bool hasInitialHitbox=true){
	this->x = x;
	this->y = y;
	this->sprite = sprite;
	this->imageIndex = -1;
	this->create();
	this->debug = false;
	this->collisionLayer = 0;
    if(hasInitialHitbox){
        this->addHitBox(0, 0, sprite->getImage(0).getSize().x, sprite->getImage(0).getSize().y, -1);
    }
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
	if(this->debug==true){
		data.drawHitBoxes = true;
	}else{
		data.drawHitBoxes = false;
	}
	data.repeated = this->sprite->repeated;
	data.width = this->sprite->width;
	data.height = this->sprite->height;

	return data;
}

//Decrement hit box counters
void Object::decHitBoxes(double delta){ //FIXME

	//If after decrementing a hitBox's time it is negative and not infinite, we need to destroy that HitBox here.
	return;
}

//Create new hit box and add it to our Object
void Object::addHitBox(int offsetX, int offsetY, int width, int height, double ttl){
	HitBox *tmp = new HitBox(offsetX,offsetY,width,height,ttl);

	this->hitBoxes.push_back(tmp);
}

//Return list of hitboxes
std::vector<HitBox *> Object::getHitBoxes(){
	return this->hitBoxes;
}

//Engine-defined process function
void Object::_process(double delta){
    process(delta); 
    decHitBoxes(1.0);
	//Calculate how long the current image has been shown, increment imageIndex if necessary
}

//Developer-defined virtual function
void Object::process(double delta){
//	basicMove(&this->x,&this->y,7,delta);
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
Object::~Object(){
	for(unsigned int i = 0; i < hitBoxes.size(); i++){
		delete hitBoxes[i];
	}
}
