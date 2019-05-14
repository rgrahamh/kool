#ifndef GAME_OBJECTS
#define GAME_OBJECTS
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "../headers/Object.hpp"
#include "../headers/Globals.hpp"
#include "scenes.hpp"


enum collideDirection {
	ABOVE = 0,
	LEFT = 1,
	RIGHT = 2,
	BELOW = 3
};

class background: public Object {

    public:
		//This code has to be present in all child objects of Object
		background(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
};

class planet: public Object {

    public:
		//This code has to be present in all child objects of Object
		planet(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
};

class asteroid: public Object {

    public:
		//This code has to be present in all child objects of Object
		bool dead;
		double deadTime;
		double deadMax;
		float rightGravBound;
		float leftGravBound;
		asteroid(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
};

class player: public Object {
	public:
		player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        float acceleration;
		bool dead;
		bool recovering;
        float maxVelocity;
        float rightGravBound;
		float leftGravBound;
        int setIndex;
		void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
        void process(double delta);
	
};

#endif