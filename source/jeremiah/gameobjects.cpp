#include "gameobjects.hpp"

using namespace std;

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
		create();
	}

void background::create(){
		this->collisionLayer = -1;
		setSprite((unsigned int)1);
	}

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

void player::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)0);
	sprite_index = 0;
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.3;
	this->acceleration = 1.0;
	this->maxVelocity = 6.5;
	this->rightGravBound = -1.0;
	this->leftGravBound = -1.0;
	this->setIndex = 0;
}

void player::process(double delta){
	//Set currect sprite
		if(Keys::isKeyPressed(Keys::W)){
			this->yA = -this->acceleration;
			this->friction = this->friction;
		}

		if(Keys::isKeyPressed(Keys::S)){
			this->yA = this->acceleration;
			this->friction = this->friction;
		}

		//Horizontal Movement
		if(Keys::isKeyPressed(Keys::D)){
			if(this->xV < this->maxVelocity){
				this->xA = this->acceleration;
			}else{
				this->xA = 0.0;
			}
			if(this->gravity==false){
				setIndex=2;
			}else{
				setIndex=4;
			}
		}
		else if(Keys::isKeyPressed(Keys::A)){
			if(this->xV > -this->maxVelocity){
				this->xA = -this->acceleration;
			}else{
				this->xA = 0.0;
			}
			if(this->gravity==false){
				setIndex=3;
			}else{
				setIndex=5;
			}
		}

		//Prevent falling off the map
		if(x+xV < 0.0 || (x+xV+this->sprite->width) > (float)getSceneWidth()){
			x-=xV;
			xV = 0.0;
			xA = 0.0;
		}

        		//Process if we are falling off our current floor
		if(((x+sprite->width) < rightGravBound || (x > leftGravBound && rightGravBound >= 0))){
			this->gravity = true;
		}
    }