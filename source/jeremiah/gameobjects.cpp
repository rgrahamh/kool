#include "gameobjects.hpp"

using namespace std;

//Background Class

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
}

void player::process(double delta){
	//Set currect sprite
		if(Keys::isKeyPressed(Keys::W) && this->gravity==false){
			this->yV = -8;
			this->gravity = true;
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
		if(Keys::isKeyPressed(Keys::S) && gravity==false){
			this->xA = 0;
			this->xV = 0;
			if(setIndex==3 || setIndex==1){
				setIndex = 9;	
			}else{
				setIndex = 6; 
			}
		}else{
			if(setIndex==6){
				setIndex = 0;
			}else if(setIndex==9){
				setIndex = 1;
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