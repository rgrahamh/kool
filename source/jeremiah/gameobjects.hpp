#ifndef GAME_OBJECTS
#define GAME_OBJECTS
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include "scenes.hpp"

class background: public Object {

    public:
		//This code has to be present in all child objects of Object
		background(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
};

class player: public Object {
	public:
		player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        float acceleration;
        float maxVelocity;
        float rightGravBound;
		float leftGravBound;
        int setIndex;
		void create();
        void process(double delta);
	
};

#endif