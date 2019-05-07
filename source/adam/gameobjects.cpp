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
	this->setText(10,10,12,false,"resources/arial.ttf",players[activePlayer].name);
	setTextColor(players[activePlayer].pColor);
	if(players[activePlayer].poweredUp==false){
		this->spriteSet = players[activePlayer].smallSet;
	}else{
		this->spriteSet = players[activePlayer].bigSet;
	}
	activeDead = false;
	this->setIndex = 0;
	this->recovering=false;
	this->finishedLevel=false;
	this->finishedFlag = false;
	this->crouching = false;
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
				//Animation step for end
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
		if((other->collisionFlags & ENEMY) !=0 && other->sprite_index!=10){
			if(direction == ABOVE && this->recovering==false){
				//We squashed them
				playSound("./resources/adam/sounds/stomp.wav");
				yV = -10.5;
			}else if(players[activePlayer].poweredUp==false && this->recovering==false){
				//We DIE
				yV = -16.0;
				gravity = true;
				this->collisionLayer = -1;
				dead = true;
				activeDead = true;	
				//Decrement how many lives we have
				players[activePlayer].lives -= 1;

				//Change whose turn it is
				if(activePlayer+1 < playerNum){
					activePlayer+=1;
				}else{
					activePlayer = 0;
				}
				while(players[activePlayer].isPlaying==false || players[activePlayer].lives < 1){
					if(activePlayer+1 < playerNum){
						activePlayer+=1;
					}else{
						activePlayer = 0;
					}
				}
				//Play dieing sound
				stopAllSounds();
				playSound("./resources/adam/sounds/die.wav");
				//Show dieing sprite
				setIndex = 6;
			}else if(players[activePlayer].poweredUp==true){
				players[activePlayer].poweredUp = false;
				this->recovering = true;
				alpha = 128;
				recoverTime = 0.0;
				int heightDiff = this->sprite->height;
				this->spriteSet = players[activePlayer].smallSet;
				setSprite(spriteSet[setIndex]);
				this->hitBoxes[0]->height = this->sprite->height;
				heightDiff = heightDiff - this->sprite->height;
				this->y += heightDiff;
				activeDead = true;
				playSound("./resources/adam/sounds/power_down.wav");
			}
		}
		if(other->collisionFlags==POWERUP and players[activePlayer].poweredUp==false){
			players[activePlayer].poweredUp=true;
			playSound("resources/adam/sounds/grow.wav");
			int heightDiff = this->sprite->height;
			this->spriteSet = players[activePlayer].bigSet;
			setSprite(spriteSet[setIndex]);
			heightDiff = heightDiff - this->sprite->height;
			this->hitBoxes[0]->height = this->sprite->height;
			this->y = this->y + heightDiff;
		}
		if(other->collisionFlags==GOAL){
			if(!finishedLevel){
				this->gravity = false;
				this->setIndex=7;
				this->finishedLevel = true;
				this->friction = 0.0;
				this->yV = 0.0;
				this->yA = 0.0;
				this->xV = 0.0;
				this->xA = 0.0;
				this->x = other->x;
				stopAllSounds();
				playSound("./resources/adam/sounds/flagpole.wav");
			}
			else if(!finishedFlag){
				this->yV = 1.0;
			}
			else{
				this->yV = 0.0;
				this->xV = 2.0;
				setIndex=2;
			}
		}
		if(other->collisionFlags==0x60){
			this->xV = 0.0;
			this->xA = 0.0;
			destroyObject(this);
		}
	}
}

void player::process(double delta){
	//Set currect sprite
	setSprite(spriteSet[setIndex]);
	if(dead==false){ //Do stuff if we're not dead
		//Jumping
		if(Keys::isKeyPressed(Keys::W) && this->gravity==false && !finishedLevel){
			this->yV = -8;
			this->gravity = true;
			if(players[activePlayer].poweredUp==false){
				playSound("./resources/adam/sounds/jump.wav");
			}else{
				playSound("./resources/adam/sounds/jump_big.wav");
			}
			this->addHitBox(this->sprite->width/2-3,0,6,this->sprite->height-2);
		}
		if(!Keys::isKeyPressed(Keys::W) && this->gravity==true && yV < 0.0){
			yV = 3*(yV/4);
		}
		//Horizontal Movement
		if(Keys::isKeyPressed(Keys::D) && !finishedLevel && !crouching){
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
		else if(Keys::isKeyPressed(Keys::A) && !finishedLevel && !crouching){
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
		}else if(!finishedLevel){
			if(this->gravity==false){
				if(this->xV >= 0.0 && this->setIndex!=6 && this->setIndex!=9){
					setIndex=0;
				}else if(this->setIndex!=9 && this->setIndex!=6){
					setIndex=1;
				}
			}else{
				if(this->xV >= 0.0){
					setIndex=4;
				}else{
					setIndex=5;
				}
			}
		}
		if(Keys::isKeyPressed(Keys::S) && players[activePlayer].poweredUp==true && gravity==false && !finishedLevel){
			this->friction = 0.1;
			if(setIndex==3 || setIndex==1){
				setIndex = 9;	
			}else{
				setIndex = 6; 
			}
			crouching = true;
			this->hitBoxes[0]->height = this->sprite->height-10;
			this->hitBoxes[0]->offsetY = 10;
		}else{
			if(!finishedLevel){
				this->friction = 0.3;
			}
			if(setIndex==6){
				setIndex = 0;
			}else if(setIndex==9){
				setIndex = 1;
			}
			crouching = false;
			this->hitBoxes[0]->height = this->sprite->height;
			this->hitBoxes[0]->offsetY = 0;
		}

		//Prevent falling off the map
		if(x+xV < 0.0 || (x+xV+this->sprite->width) > (float)getSceneWidth()){
			x-=xV;
			xV = 0.0;
			xA = 0.0;
		}

		//Process if we are falling off our current floor
		if(((x+sprite->width) < rightGravBound || (x > leftGravBound && rightGravBound >= 0)) && !finishedLevel){
			this->gravity = true;
		}
		//Process if we are jumping, if so add the jump hit box
		if(yV < 0.0 && hitBoxes.size() < 2){
			//pass
		}else if ((yV > 0.0 || (setIndex!=4 && setIndex !=5)) && hitBoxes.size() >= 2){
			this->deleteHitBox(1);
		}
	}else{
		//Determine whether to go to preview scene or gameover scene
		bool allDead = true;
		deathTime += delta;
		if(deathTime > deathMax){
			for(int i = 0; i < playerNum; i++){
				if(players[i].lives>0 && players[i].isPlaying==true){
					allDead = false;
				}
			}
			if(allDead == true){
				setActiveScene(3);
				stopAllSounds();
				playSound("./resources/adam/sounds/gameover.wav");
			}else{
				//Setup preview scene
				resetScene(createPreviewScene,2);
				setActiveScene(2);
			}
		}
	}
	//Recovery
	if(recoverTime < 1200.0){
		recoverTime+=delta;
	}else if(recovering==true){
		recovering=false;
		activeDead=false; 
		alpha = 255;
	}
}

//Block class

Block::Block(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void Block::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)56);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void Block::onCollide(Object *other, int myBoxID, int otherBoxID){
	//Determine what direction we are hitting at
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
		else if(this->y < (otherBoxY-other->yV)){
			direction = ABOVE;
		}else{
			direction = BELOW;
		}
	if(other->collisionFlags==PLAYER && players[activePlayer].poweredUp){
		if(other->sprite_index==players[activePlayer].bigSet[4] || other->sprite_index==players[activePlayer].bigSet[5]){
			if(otherBoxID==1){
			playSound("resources/adam/sounds/break.wav");
			destroyObject(this);
			}
		}
	}
}
//metalBlock class

metalBlock::metalBlock(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void metalBlock::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)48);
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

//staticPipe class

staticPipe::staticPipe(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	create();
}

void staticPipe::create(){
	this->collisionLayer = 0;
	this->debug = false;
	setSprite((unsigned int)55);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);

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
	this->addHitBox(2,5,this->sprite->width-2,this->sprite->height-5);
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
		if(direction == BELOW && activeDead==false){
			this->dead = true;
			this->xV = 0.0;
			setSprite((unsigned int)10);
		}
	}
	if((other->collisionFlags & DANGER_ALL) != 0){
		dead = true;
		this->collisionLayer = -1;
		this->collisionFlags = 0;
		yV = -9.0;
		gravity = true;
		setSprite((unsigned int)54);
		playSound("resources/adam/sounds/kick.wav");
	}
}
void gomba::process(double delta){

	if(dead==false){
		//Prevent falling off the map
		if(x+xV < 0.0 || (x+xV+this->sprite->width) > (float)getSceneWidth()){
			x-=xV;
			xV = -xV;
		}

		//Process if we are falling off our current floor
		if((x+sprite->width) < rightGravBound || (x > leftGravBound && rightGravBound >= 0)){
			this->gravity = true;
		}
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
		for(int i = 0; i < playerNum; i++){
			players[i].lives = 3;
		}
		resetScene(gameoverScene,3);
		resetScene(levelFunc,1);
		resetScene(createPreviewScene,2);
		setActiveScene(2);	
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

//MysteryBox class
MysteryBox::MysteryBox(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void MysteryBox::create(){
	this->beenHit = false;
	this->collisionFlags = GROUND;
	setSprite((unsigned int)12);
	this->debug=false;
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->animationDelay = 70.0;
}

void MysteryBox::onCollide(Object *other, int myBoxID, int otherBoxID){

	//Determine the direction of the collision
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
	else if(this->y < (otherBoxY-other->yV)){
		direction = ABOVE;
	}else{
		direction = BELOW;
	}
	if(other->collisionFlags==PLAYER && direction==ABOVE){
		if(beenHit==false){
			mushroom *tmp = new mushroom(this->x,this->y-1,0,POWERUP,false);
			playSound("./resources/adam/sounds/mushroom_up.wav");
			createObject(tmp);
			beenHit = true;
			setSprite((unsigned int)13);
		}else if(other->yV <= 0.0){
			playSound("./resources/adam/sounds/bump.wav");
		}
	}	
}

//mushroom class
mushroom::mushroom(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void mushroom::create(){
	setSprite((unsigned int)31);
	//Keep track of full sprite height, which is 20px
	sprFullHeight = 16;
	rate = 1;
	this->sprite->setSize(this->sprite->width,rate);
	full = false;
	animationTime = 20.0;
	animationAcc = 0.0;
	this->debug = false;
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void mushroom::process(double delta){
	if(full == false){
		animationAcc+=delta;
		if(animationAcc >= animationTime){
			this->sprite->setSize(this->sprite->width,this->sprite->height+rate);
			this->y-=rate;
			this->hitBoxes[0]->height = this->sprite->height;
			if(this->sprite->height >= sprFullHeight){
				full = true;
				this->gravity = true;
				this->xV = 2.0;
			}
			animationAcc = 0.0;
		}
	}else{
		//Process if we are falling off our current floor
		if((x+sprite->width) < rightGravBound || (x > leftGravBound && rightGravBound >= 0)){
			this->gravity = true;
		}
	}
}

void mushroom::onCollide(Object *other, int myBoxID, int otherBoxID){
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
	else if(other->collisionFlags==PLAYER){
		destroyObject(this);
	}
	return;
}
//flagpole class
flagpole::flagpole(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void flagpole::create(){
	setSprite((unsigned int)46);
	this->debug = false;
	this->addHitBox(10,20,this->sprite->width-10,this->sprite->height-20);
}

void flagpole::process(double delta){
	return;
}

void flagpole::onCollide(Object *other, int myBoxID, int otherBoxID){
	if(other->collisionFlags==PLAYER){
		this->myFlag->y = other->y;
	}
	return;
}

//castle class

castle::castle(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();

}

void castle::create(){
	setSprite((unsigned int)49);
	this->debug =false;
	this->addHitBox(30,40,20,40);
	this->collisionFlags = 0x60;
}

void castle::process(double delta){
	return;
}

void castle::onCollide(Object *other, int myBoxID, int otherBoxID){
	if(other->collisionFlags==PLAYER){
			//Change whose turn it is
			if(activePlayer+1 < playerNum){
				activePlayer+=1;
			}else{
				activePlayer = 0;
			}
			while(players[activePlayer].isPlaying==false || players[activePlayer].lives<1){
				if(activePlayer+1 < playerNum){
					activePlayer+=1;
				}else{
					activePlayer = 0;
				}
			}
			//Set the level
			//Start new level timer	
			sceneChange = new timeTrigger(0,0);
			sceneChange->setTimer(1500.0);
			sceneChange->setSceneFunc(createPreviewScene);
			sceneChange->setSceneID(2);
			createObject(sceneChange);
	}
}
aFlag::aFlag(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();
}

void aFlag::create(){
	setSprite((unsigned int)47);	
}

void aFlag::process(double delta){
	return;
}

void aFlag::onCollide(Object *other, int myBoxID, int otherBoxID){
	return;
}
