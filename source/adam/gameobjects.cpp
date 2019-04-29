#include "gameobjects.hpp"
#include "globalvars.hpp"

using namespace std;

//Background Class

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
		create();
	}

void background::create(){
		this->collisionLayer = -1;
		setSprite((unsigned int)1);
	}

//Player Class

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
	if(activePlayer==1){
		this->setText(10,10,12,false,"resources/arial.ttf","Gracin");
	}else{
		this->setText(10,10,12,false,"resources/arial.ttf","Owen");
	}
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
			playSound("./resources/adam/sounds/stomp.wav");
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
			if(activePlayer==1){
				p1Lives -= 1;
				activePlayer = 2;
			}else{
				p2Lives -= 1;
				activePlayer = 1;
			}
			playSound("./resources/adam/sounds/die.wav");
			resetScene(createPreviewScene,2);
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
			playSound("./resources/adam/sounds/jump.wav");
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
			if(p1Lives < 1 && p2Lives < 1){
				setActiveScene(3);
				playSound("./resources/adam/sounds/gameover.wav");
			}else{
				setActiveScene(2);
			}
		}
	}
}

//Block class

Block::Block(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void Block::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)8);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

//ground class

ground::ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void ground::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)2);
	this->addHitBox(0,153,this->sprite->width,25);

}

//Gomba class

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

//genericText class

genericText::genericText(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void genericText::create(){
	return;
}

//gameTrigger class
gameTrigger::gameTrigger(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void gameTrigger::create(){
	return; 
}

void gameTrigger::process(double delta){
	if(Keys::isKeyPressed(Keys::X)){
		levelFunc = level1;
		p1Lives = 3;
		p2Lives = 3;
		resetScene(gameoverScene,3);
		resetScene(levelFunc,1);
		setActiveScene(1);	
	}
}

//timeTrigger class
timeTrigger::timeTrigger(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void timeTrigger::create(){
	this->maxTime = -1.0;
	this->totalTime = 0.0;
}

void timeTrigger::process(double delta){
	if(this->maxTime > 0.0){
		this->totalTime += delta;
		if(this->totalTime >= maxTime){
			resetScene(this->jumpScene,this->sceneID);
			setActiveScene(this->sceneID);
		}
	}
}

void timeTrigger::setTimer(double ms){
	this->maxTime = ms;
	this->totalTime = 0.0;
}

void timeTrigger::setSceneID(unsigned int sID){
	this->sceneID = sID;
}

void timeTrigger::setSceneFunc(std::function<Scene *()>jumpScene){
	this->jumpScene = jumpScene;
}
