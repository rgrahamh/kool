#include "./headers/gameobjects.hpp"
#include <vector>

using namespace std;

//Background object
Background::Background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Background::create(){
    setSprite((unsigned int) 0);
}

//Player object
Player::Player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Player::create(){
    this->collisionLayer = 0;
    this->collisionFlags = PLAYER;
    this->debug = true;

    //Adding all of the Mega Man sprites to a list
    sprites.push_back(getSprite(1));
    sprites.push_back(getSprite(2));
    sprites.push_back(getSprite(3));
    sprites.push_back(getSprite(4));
    sprites.push_back(getSprite(5));
    sprites.push_back(getSprite(6));
    sprites.push_back(getSprite(7));
    sprites.push_back(getSprite(8));
    sprites.push_back(getSprite(9));
    sprites.push_back(getSprite(10));

    this->setSprite(sprites[0]);

	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.3;
	this->speed = 2.0;
	this->maxVelocity = 8.0;
    this->collisionLayer = 0;

    grounded = false;
    gravity = false;
}

void Player::onCollide(Object *other, int myBoxID, int otherBoxID){
    //If the player collides with ground:
    if(other->collisionFlags & GROUND){
        int thisX = this->x + this->hitBoxes[myBoxID]->offsetX;
        int thisY = this->y + this->hitBoxes[myBoxID]->offsetY;

        int oldThisX = this->xPrev + this->hitBoxes[myBoxID]->offsetX;
        int oldThisY = this->yPrev + this->hitBoxes[myBoxID]->offsetY;

        int otherX = other->x + other->hitBoxes[otherBoxID]->offsetX;
        int otherY = other->y + other->hitBoxes[otherBoxID]->offsetY;

        int oldOtherX = other->xPrev + this->hitBoxes[otherBoxID]->offsetX;
        int oldOtherY = other->yPrev + this->hitBoxes[otherBoxID]->offsetY;

        //Bottom of this colllides with top of other
        if(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height < oldOtherY){
            this->y = otherY - this->hitBoxes[otherBoxID]->height;
            this->yV = 0;
            grounded = true;
        }
        //Top of this collides with bottom of other
        else if(thisY <= otherY + other->hitBoxes[myBoxID]->height && oldThisY > oldOtherY + other->hitBoxes[myBoxID]->height){ 
            this->y = otherY + other->hitBoxes[myBoxID]->height;
            this->yV = 0;
        }
        //Left side of this collides with right side of other
        else if(thisX + this->hitBoxes[myBoxID]->width >= otherX && oldThisX + this->hitBoxes[myBoxID]->width < oldOtherX){ 
            this->x = otherX + this->hitBoxes[otherBoxID]->width;
            this->xV = 0;
        }
        //Right side of this collides with left side of other
        else if(thisX <= otherX + other->hitBoxes[myBoxID]->width && oldThisX > oldOtherX + other->hitBoxes[myBoxID]->width){ 
            this->x = otherX - this->hitBoxes[myBoxID]->width;
            this->xV = 0;
        }
    }
}

void Player::process(float delta){
    grounded = false;
    if(Keys::isKeyPressed(Keys::W) && grounded){
        yA += 15.0;
    }
    if(Keys::isKeyPressed(Keys::A)){
        xA += speed;
    }
    if(Keys::isKeyPressed(Keys::D)){
        xA -= speed;
    }
    if(Keys::isKeyPressed(Keys::Space)){
        //Shoot
        yA += 15.0;
    }
}

Ground::Ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Ground::create(){
    this->collisionLayer = 0;
    this->debug=true;
    this->collisionFlags = GROUND;

    setSprite((unsigned int)11);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}
