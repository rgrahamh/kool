#include "gameobjects.hpp"
#include "globalvars.hpp"

using namespace std;

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
		create();
	}

void background::create(){
		this->collisionLayer = -1;
		setSprite((unsigned int)2); //index 2
	}

planet::planet(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
		create();
	}

void planet::create(){
		this->collisionLayer = 0;
		setSprite((unsigned int)1); //index1
	}

asteroid::asteroid(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
		create();
	}

void asteroid::create(){

		this->collisionLayer = 0;
		this->debug = false;
		this->collisionFlags = ENEMY;
		this->addHitBox(2,5,this->sprite->width-2,this->sprite->height-5);
		this->dead = false;
		deadTime = 0.0;
		deadMax = 300.0;
		setSprite((unsigned int)4); //index 4
	}

void asteroid::onCollide(Object *other, int myBoxID, int otherBoxID){

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

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
			create(); 
		}

void player::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)0);//index 0
	sprite_index = 0;
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.3;
	this->acceleration = 1.0;
	this->maxVelocity = 6.5;
	this->rightGravBound = -1.0;
	this->leftGravBound = -1.0;
	this->setIndex = 0;
	activeDead = false;
}

void player::process(double delta){
	//Set currect sprite
		if(Keys::isKeyPressed(Keys::W)){
			this->yV = -2;
			this->friction = this->friction;
			this->yA = -this->acceleration;
		}

		if(Keys::isKeyPressed(Keys::S)){
			this->yV = 2;
			this->friction = this->friction;
			this->yA = this->acceleration;
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


void player::onCollide(Object *other, int myBoxID, int otherBoxID){
	if(myBoxID==0){	
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
			else if(this->y-yV+this->sprite->height <= otherBoxY && gravity==true){
				direction = ABOVE;
			}else{
				direction = BELOW;
			}
		if(other->collisionFlags==GROUND && dead==false){
			if(!finishedFlag && finishedLevel){
				finishedFlag = true;
				y-=1;
				stopAllSounds();
				playSound("./resources/adam/sounds/stage_clear.wav");
			}
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
				if(yV!=0.0){
					this->yV = 0.5;
					this->yA = 0.0;
				}else{
					this->xV = 1.0;
				}
			}
		}
		if((other->collisionFlags & ENEMY) !=0){
			if(direction == ABOVE && this->recovering==false){
				this->gravity=false;
			}else if(this->recovering==false){
				gravity = true;
				this->collisionLayer = -1;
				dead = true;
				activeDead = true;	
			}
		}
		if(other->collisionFlags==0x60){
			this->xV = 0.0;
			this->xA = 0.0;
			destroyObject(this);
		}
	}
}

	
