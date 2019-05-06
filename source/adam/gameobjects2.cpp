#include "gameobjects.hpp"
#include "globalvars.hpp"

using namespace std;

koopa::koopa(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav){
	this->create();	  
	  
}

void koopa::create(){
	inShell = false;
	dead = false;
	shellMoving = false;
	timeInShell = 0.0;
	debug = true;
	setSprite((unsigned int)53);
	shellSpeed = 3.0;
	addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void koopa::onCollide(Object *other, int myBoxID, int otherBoxID){
	//Determine what direction we are hitting the ground at
		enum collideDirection direction;
		float otherBoxX = other->x+other->hitBoxes[otherBoxID]->offsetX;
		float otherBoxY = other->y+other->hitBoxes[otherBoxID]->offsetY;
		int otherBoxWidth = other->hitBoxes[otherBoxID]->width;

		if((this->x+sprite->width-xV) < (otherBoxX - other->xV)){
			direction = LEFT;
		}
		else if((this->x-xV) > (otherBoxX + otherBoxWidth - other->xV)){
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
	if(other->collisionFlags==PLAYER){
		if(activeDead==false){
			if(direction == BELOW){
				if(inShell==false){
					inShell = true;
					timeInShell = 0.0;
					this->xV = 0.0;
					y+=9;
					this->hitBoxes[0]->height -= 9;
				}
				if(shellMoving==true){
					shellMoving = false;
					xV = 0.0;
				}
			}
			else if(direction == LEFT && inShell==true){
				xV = -shellSpeed;
				x-=this->sprite->width / 2;
				shellMoving = true;
			}
			else if(direction == RIGHT && inShell==true){
				xV = shellSpeed;
				x+=this->sprite->width / 2;
				shellMoving = true;
			}
		}
	}
	if((other->collisionFlags & DANGER_ALL) !=0 && inShell==false){
		dead = true;
		this->collisionLayer = -1;
		this->collisionFlags = 0;
		yV = -9.0;
		gravity = true;
		setSprite((unsigned int)51);
	}
}

void koopa::process(double delta){
	//Housekeeping
	if(dead==false){
		if(inShell==true){
			if(!shellMoving){
				collisionFlags = 0x99;
				timeInShell+=delta;
			}else if(timeInShell > 50.0){
				collisionFlags = ENEMY | DANGER_ALL;
			}	
			if(timeInShell < 3000.0){
				setSprite((unsigned int)51);
			}else if(timeInShell < 3200.0){
				setSprite((unsigned int)52);
			}else{
				inShell=false;
				y-=9;
				this->hitBoxes[0]->height += 9;
				xV = 1.0;
			}
		}else{
			collisionFlags = ENEMY;
			if(xV > 0.0){
				setSprite((unsigned int)53);
			}else if(xV < 0.0){
				setSprite((unsigned int)50);
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
	

	//Destroy us if we're outside the room
	if(y > (float)getSceneHeight()){
		destroyObject(this);
	}

}
