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
    this->debug = true;
    this->addHitBox(0, 0, this->sprite->width, this->sprite->height);
}

void hurdle::init()
{
    this->collisionLayer = 1;
    setSprite( (unsigned int) 3);
}
