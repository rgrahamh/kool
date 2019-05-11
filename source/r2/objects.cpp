#include "objects.h"
#include <iostream>
using namespace std;

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void player::init() {
    setSprite((unsigned int) 2);
    this->debug = true;
    this->addHitBox(13, 3, 6, this->sprite->height - 3);
}

void player::onCollide(Object *other, int myBoxID, int otherBoxID) {
    if(this->x > other->x && other->collisionFlags == GROUND) {
        this->gravity = false;
		this->on_ground = true;
        this->yV = 0.0;
		this->yA = 0.0;
		this->y = 512 - (other->sprite->height + this->sprite->height); // put them on the ground
    }
}

void player::process(double delta) {
    if(this->on_ground && Keys::isKeyPressed(Keys::W)) {
		this->on_ground = false;
        this->gravity = true;
        this->y = 64;
    }
	// this->x += 5;
	/*
    if(Keys::isKeyPressed(Keys::A)) {
        this->x -= 5;
    }
    if(Keys::isKeyPressed(Keys::S)) {
        this->y += 5;
    }
    if(Keys::isKeyPressed(Keys::W)) {
        this->y -= 5;
    }
	*/
}


hurdle::hurdle(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void hurdle::init() {
    setSprite((unsigned int) 3);
}

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void background::init() {
    setSprite( (unsigned int) 0);
}


ground::ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void ground::init() {
    this->debug = true;
    setSprite((unsigned int) 4);
    this->addHitBox(0,0, this->sprite->width, this->sprite->height);
}
