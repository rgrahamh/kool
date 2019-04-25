#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

enum collideDirection {
	ABOVE = 0,
	LEFT = 1,
	RIGHT = 2,
	BELOW = 3
};

class background: public Object {

    public:

		//This code has to be present in all child objects of Object
		background(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

		void create(){
			this->collisionLayer = -1;
			setSprite((unsigned int)1);
		}

};

class player: public Object {
	public:
		float acceleration;
		float maxVelocity;
		float rightGravBound;
		float leftGravBound;

		player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

		void create(){
			this->collisionLayer = 0;
			this->debug = false;
			setSprite((unsigned int)0);
			sprite_index = 0;
			this->addHitBox(0,0,this->sprite->width,this->sprite->height);
			this->friction = 0.3;
			this->acceleration = 1.0;
			this->maxVelocity = 6.5;
			this->animationDelay = 40.0;
			this->rightGravBound = -1.0;
			this->leftGravBound = -1.0;
		}

		
		void onCollide(Object *other, int myBoxID, int otherBoxID){
				
			//Determine what direction we are hitting the ground at
				enum collideDirection direction;
				float otherBoxX = other->x+other->hitBoxes[otherBoxID]->offsetX;
				float otherBoxY = other->y+other->hitBoxes[otherBoxID]->offsetY;
				int otherBoxWidth = other->hitBoxes[otherBoxID]->width;

				if((this->x+sprite->width-xV) < otherBoxX){
					direction = LEFT;
				}
				else if((this->x-xV) > (otherBoxX + otherBoxWidth)){
					direction = RIGHT;
				}
				else if(this->y-yV < otherBoxY && gravity==true){
					direction = ABOVE;
				}else{
					direction = BELOW;
				}

			if(other->collisionFlags==GROUND){
				if(direction == ABOVE){
					this->gravity = false;
					this->rightGravBound = otherBoxX;
					this->leftGravBound = otherBoxX + otherBoxWidth;
					this->yA = 0.0;
					this->yV = 0.0;

					//Calculate correct y value
					float offsetY = other->hitBoxes[otherBoxID]->offsetY;

					this->y = ((other->y+offsetY)-(this->sprite->height)-1);
				}
				if(direction == LEFT || direction == RIGHT){
					this->x-=this->xV;
					this->xV = 0.0;
					this->xA = 0.0;
				}
				if(direction == BELOW){
					this->yV = 0.0;
					this->yA = 0.0;
				}
			}
		}

		void process(double delta){

			//Jumping
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
					setSprite((unsigned int)3);
				}else{
					setSprite((unsigned int)6);
				}
			}
			else if(Keys::isKeyPressed(Keys::A)){
				if(this->xV > -this->maxVelocity){
					this->xA = -this->acceleration;
				}else{
					this->xA = 0.0;
				}
				if(this->gravity==false){
					setSprite((unsigned int)5);
				}else{
					setSprite((unsigned int)7);
				}
			}else{
				if(this->gravity==false){
					if(this->xV >= 0.0){
						setSprite((unsigned int)0);
					}else{
						setSprite((unsigned int)4);
					}
				}else{
					if(this->xV >= 0.0){
						setSprite((unsigned int)6);
					}else{
						setSprite((unsigned int)7);
					}
				}
			}

			//Prevent falling off the map
			if(x+xV < 0.0 || (x+xV+this->sprite->width) > (float)getSceneWidth()){
				x-=xV;
				xV = 0.0;
				xA = 0.0;
			}

			//Process if we are falling off our current floor
			if((x+sprite->width) < rightGravBound || (x > leftGravBound && rightGravBound >= 0)){
				this->gravity = true;
			}
		}
		

};

class Block: public Object {
	public:
		Block(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}
	
		void create(){
			this->collisionLayer = 0;
			this->debug = false;
			setSprite((unsigned int)8);
			this->addHitBox(0,0,this->sprite->width,this->sprite->height);
		}
};

class ground: public Object {
	public:
		ground(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

		void create(){
			this->collisionLayer = 0;
			this->debug = false;
			setSprite((unsigned int)2);
			this->addHitBox(0,153,this->sprite->width,25);

		}

};

