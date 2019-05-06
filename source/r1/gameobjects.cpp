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
    this->debug = false;

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
}

Ground::Ground(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Ground::create(){
    setSprite((unsigned int)11);
}
