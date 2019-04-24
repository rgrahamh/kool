#include "headers/Object.hpp"
#include "headers/Sprite.hpp"
#include "headers/Globals.hpp"
#include <iostream>

#define Keys sf::Keyboard

using namespace std;

std::vector<Sprite *>spriteIndex = std::vector<Sprite *>();

Object::Object(float x, float y, int collisionlayer, unsigned int collisionFlags, bool grav){
	this->x = x;
	this->y = y;
	this->xPrev = x;
	this->yPrev = y;
	this->xV = 0;
	this->yV = 0;
    this->xA = 0;
    this->yA = 0;
	this->friction = 0.0;
	this->sprite = NULL;
	this->imageIndex = -1;
	this->create();
	this->debug = false;
	this->animationTime = 0;
	this->animationDelay = 50; //Default to 50 MS animation
    this->collisionFlags = collisionFlags;
	this->collisionLayer = collisionLayer;
    this->gravity = grav;
}

Object::~Object(){
	for(unsigned int i = 0; i < hitBoxes.size(); i++){
		delete hitBoxes[i];
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
void Object::_process(double delta, float grav, float termVel){
    process(delta); 
    _processPhysics(grav, termVel);
    decHitBoxes(delta);
	this->xPrev = x;
	this->yPrev = y;
	_animate(delta);

	//Calculate how long the current image has been shown, increment imageIndex if necessary
}

//Engine-defined animation calculations
void Object::_animate(double delta){
	animationTime += delta;
	if(animationTime >= animationDelay){//Time to switch
		if(this->imageIndex < (this->sprite->getImageNum()-1)){
			this->imageIndex += 1;
		}else{
			this->imageIndex = 0;
		}
		animationTime = 0.0;
	}
}

//Developer-defined virtual function
void Object::process(double delta){
//	basicMove(&this->xA,&this->yA,7,delta);
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

void Object::_processPhysics(float grav, float termVel){
	
	//Change x acceleration/velocity based on friction
	if(xV != 0.0){
		xV = xV * (1.0-friction);
	}

    //Adding horizontal acceleration to the horizontal velocity
    xV += xA;
    xA = 0;

    //Capping the horizontal velocity at +/- maxSpeed
    if(xV > termVel){
        xV = termVel;
    }
    else if(xV < (termVel * -1)){
        xV = termVel * -1;
    }

    //Change x position based on horizontal velocity
    x += xV;

    //Adding gravity to vertical acceleration (implies that gravity is always up or down)
    if(this->gravity){
        yA =+ grav;
    }

    //Adding vertical acceleration to the vertical velocity
    yV += yA;
    yA = 0;

    //Capping the vertical velocity at +/- terminal velocity
    if(yV > termVel){
        yV = termVel;
    }
    else if(yV < (termVel * -1)){
        yV = termVel * -1;
    }

    //Change y position based on vertical velocity
    y += yV;
}
