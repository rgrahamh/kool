#include "objects.h"
#include <iostream>
using namespace std;

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void player::init() {
    this->collisionLayer = 1;
    setSprite((unsigned int) 2);
    this->debug = true;
    this->addHitBox(0, 0, this->sprite->width, this->sprite->height);
    // this->spriteSet
}

void player::on_collide(Object *other, int myBoxID, int otherBoxID) {
    std::cout << "Ha" << std::endl;
}

void player::process(double delta) {
    if(Keys::isKeyPressed(Keys::D)) {
        this->x += 5;
        this->change_sprite();
    }
    else if(Keys::isKeyPressed(Keys::A)) {
        this->x -= 5;
        this->change_sprite();
    }
    else if(Keys::isKeyPressed(Keys::S)) {
        this->y += 5;
        this->change_sprite();
    }
    else if(Keys::isKeyPressed(Keys::W)) {
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
    this->collisionLayer = 1;
    setSprite( (unsigned int) 3);
}

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    init();
}

void background::init() {
    this->collisionLayer = 0;
    setSprite( (unsigned int) 0);
}
