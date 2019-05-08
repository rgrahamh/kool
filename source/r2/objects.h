#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H

class player: public Object {
public:
    std::vector<unsigned int> spriteSet;
    player(float x, float y, int collisionLayer=1, unsigned int collisionFlags=0, bool grav=true);
    void init();
    void onCollide(Object *other, int myBoxID, int otherBoxID);
    void process(double delta);
};

class hurdle: public Object {
public:
    hurdle(float x, float y, int collisionLayer=1, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class background: public Object
{
    background(float x, float y, int collisionLayer=1, unsigned int collisionFlags=0, bool grav=false);
    void init();
}

#endif
