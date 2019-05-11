
#ifndef OBJECTS_H
#define OBJECTS_H
#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include <vector>

class player: public Object {
private:
    int set_index = 0;
	bool on_ground = true;
public:
    void change_sprite();
    std::vector<unsigned int> spriteSet;
    player(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=true);
    void init();
    void onCollide(Object *other, int myBoxID, int otherBoxID);
    void process(double delta);
};

class hurdle: public Object {
public:
    hurdle(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class background: public Object
{
public:
    background(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

class ground: public Object {
public:
    ground(float x, float y, int collisionLayer=0, unsigned int collisionFlags=0, bool grav=false);
    void init();
};

#endif
