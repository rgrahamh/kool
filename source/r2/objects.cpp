#include "objects.h"
#include <iostream>
using namespace std;

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void player::init() {
    setSprite((unsigned int) 1);
    this->debug = true;
    this->addHitBox(0, 0, this->sprite->width, this->sprite->height);
}

void player::onCollide(Object *other, int myBoxID, int otherBoxID) {
    std::cout << "Ha" << std::endl;
    if(this->x > other->x && other->collisionFlags == GROUND) {
        this->y = other->y - (this->sprite_height * 2 + 5);
    }
}

void player::process(double delta) {
    if(Keys::isKeyPressed(Keys::D)) {
        this->x += 5;
        this->change_sprite();
    }
    if(Keys::isKeyPressed(Keys::A)) {
        this->x -= 5;
        this->change_sprite();
    }
    if(Keys::isKeyPressed(Keys::S)) {
        this->y += 5;
        this->change_sprite();
    }
    if(Keys::isKeyPressed(Keys::W)) {
        this->y -= 5;
        this->change_sprite();
    }
}

void player::change_sprite() {
    if(!this->set_index) this->set_index = 1;
    else this->set_index = 0;
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
