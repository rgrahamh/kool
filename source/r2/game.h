#include <iostream>
#include "../headers/Object.hpp"

#ifndef GAME_H
#define GAME_H

class Runner: public Object
{
public:
    /* attributes */
    int x_pos;
    long distance = 0;

    /* methods */
    void run();

};

class background: public Object
{
public:
    background(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
    void create();
};

#endif
