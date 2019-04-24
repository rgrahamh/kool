#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

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

		player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

		void create(){
			this->collisionLayer = 0;
			this->debug = true;
			setSprite((unsigned int)0);
			this->addHitBox(0,0,this->sprite->width,this->sprite->height);
			this->friction = 0.3;
			this->acceleration = 1.0;
			this->animationDelay = 1000.0;
		}

		
		void onCollide(Object *other, int myBoxID, int otherBoxID){
			if(other->collisionFlags==GROUND){
				this->gravity = false;
				this->yA = 0.0;
				this->yV = 0.0;
				//Calculate correct y value
				float offsetY = other->hitBoxes[otherBoxID]->offsetY;

				this->y = ((other->y+offsetY)-(this->sprite->height)-1);
			}
		}

		void process(double delta){
			if(Keys::isKeyPressed(Keys::W) && this->gravity==false){
				this->yV = -8;
				this->gravity = true;
			}
			if(Keys::isKeyPressed(Keys::D)){
				if(this->xV < 5.0){
					this->xA = this->acceleration;
				}else{
					this->xA = 0.0;
				}
			}
			else if(Keys::isKeyPressed(Keys::A)){
				if(this->xV > -5.0){
					this->xA = -this->acceleration;
				}else{
					this->xA = 0.0;
				}
			}
		}
		

};

class ground: public Object {
	public:
		ground(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false):Object(x,y,collisionLayer,collisionFlags,grav){
			create();
		}

		void create(){
			this->collisionLayer = 0;
			this->debug = true;
			setSprite((unsigned int)2);
			this->addHitBox(0,153,this->sprite->width,25);

		}

};
