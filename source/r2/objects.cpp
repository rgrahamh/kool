#include "objects.h"

player::player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav)
    :Object(x,y,collisionLayer,collisionFlags,grav) 
{
    init();
}

void player::init() 
{
    this->collisionLayer = 1;
    setSprite( (unsigned int) 1);
}