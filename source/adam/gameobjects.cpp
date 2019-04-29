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
		this->animationDelay = 40.0;
		this->rightGravBound = -1.0;
		this->leftGravBound = -1.0;
		this->deathTime = 0.0;
		this->deathMax = 2000.0;
		dead = false;
		this->setText(50,50,12,false,"resources/arial.ttf","Mario");
	}

		
void player::onCollide(Object *other, int myBoxID, int otherBoxID){
		
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

	if(other->collisionFlags==GROUND && dead==false){
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
	if(other->collisionFlags==ENEMY && other->sprite_index!=10){
		if(direction == ABOVE){
			//We squashed them
			yV = -4.0;
		}else{
			//We DIE
			yV = -16.0;
			gravity = true;
			this->collisionLayer = -1;
			if(direction == LEFT || direction == BELOW){
				xV = -10.0;
			}else{
				xV = 10.0;
			}
			dead = true;
			setSprite((unsigned int)11);
		}
	}
}

void player::process(double delta){
	if(dead==false){ //Do stuff if we're not dead
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
				if(this->xV >= 0.0 && this->sprite_index!=6){
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
	}else{
		deathTime += delta;
		if(deathTime > deathMax){
			resetScene(createGameScene,0);
		}
	}
}

Block::Block(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void Block::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)8);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

ground::ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void ground::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)2);
	this->addHitBox(0,153,this->sprite->width,25);

}


gomba::gomba(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}
void gomba::create(){
	this->collisionLayer = 0;
	this->debug = false;
	this->collisionFlags = ENEMY;
	setSprite((unsigned int)9);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->dead = false;
	deadTime = 0.0;
	deadMax = 300.0;
}

void gomba::onCollide(Object *other, int myBoxID, int otherBoxID){

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

	//Interact with walls, floor, ceiling
	if(other->collisionFlags==GROUND){
		if(direction == ABOVE){
			this->gravity = false;
			this->rightGravBound = otherBoxX;
			this->leftGravBound = otherBoxX + otherBoxWidth;
			this->yA = 0.0;
			this->yV = 0.0;
			this->xV = 1.0;

			//Calculate correct y value
			float offsetY = other->hitBoxes[otherBoxID]->offsetY;

			this->y = ((other->y+offsetY)-(this->sprite->height)-1);
		}
		if(direction == LEFT || direction == RIGHT){
			this->x-=this->xV;
			this->xV = -xV;
			this->xA = 0.0;
		}
		if(direction == BELOW){
			this->yV = 0.0;
			this->yA = 0.0;
			this->xV = -xV;
		}
	}
	if(other->collisionFlags==PLAYER && dead==false){
		if(direction == BELOW && other->sprite_index!=11){
			this->dead = true;
			this->xV = 0.0;
			setSprite((unsigned int)10);
		}
	}
}
void gomba::process(double delta){

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

	//Time before we disappear
	if(dead==true){
		deadTime += delta;
		if(deadTime > deadMax){
			destroyObject(this);
		}
	}
}
