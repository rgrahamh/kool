#include "headers/Globals.hpp"

#define Keys sf::Keyboard
void basicMove(float *x, float *y, int speed, double delta){
	if(Keys::isKeyPressed(Keys::D)){
        *x += speed * delta;
    }
    if(Keys::isKeyPressed(Keys::A)){
        *x -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::W)){
        *y -= speed * delta;
    }
    if(Keys::isKeyPressed(Keys::S)){
        *y += speed * delta;
    }
}
