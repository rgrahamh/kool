#ifndef GAME_OBJECTS
#define GAME_OBJECTS
#include <cmath>
#include <cstdlib>
#include <iostream>
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

class player: public Object {
	public:
		bool dead;
		float acceleration;
		float maxVelocity;
		float rightGravBound;
		float leftGravBound;
		double deathTime;
		double deathMax;

		player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);

		void create();

		
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		

		void process(double delta);
		

};

class Block: public Object {
	public:
		Block(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
	
		void create();
};

class ground: public Object {
	public:
		ground(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		

		void create();
	
};

class gomba: public Object {
	public:
		bool dead;
		float rightGravBound;
		float leftGravBound;
		double deadTime;
		double deadMax;

		gomba(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);

		void create();
	
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
		
};

class genericText: public Object {
	public:
		genericText(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);

		void create();
};

class gameTrigger: public Object {
	public:
		gameTrigger(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);

		void create();

		void process(double delta);
};

class timeTrigger: public Object {
	public:
		timeTrigger(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);

		void create();

		void process(double delta);

		void setTimer(double ms);

};
#endif
