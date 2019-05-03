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

class player: public Object {
	public:
		bool dead;
		bool poweredUp;
		bool recovering;
		float acceleration;
		float maxVelocity;
		float rightGravBound;
		float leftGravBound;
		double deathTime;
		double deathMax;
		double recoverTime;
		//Keeps track of what character we are.
		std::vector<unsigned int>spriteSet;
		int setIndex; 
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

class MysteryBox: public Object {
	public:
		bool beenHit;
		MysteryBox(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
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
		double maxTime; 
		double totalTime;
		std::function<Scene *()> jumpScene;
		unsigned int sceneID;
		timeTrigger(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
		void process(double delta);
		void setTimer(double ms);
		void setSceneFunc(std::function<Scene *()> jumpScene);
		void setSceneID(unsigned int sID);

};

class mushroom: public Object {
	public: 
		int type;
		int sprFullHeight;
		double animationTime;
		double animationAcc;
		int rate;
		bool full;

		mushroom(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void create();
		void process(double delta);
		void onCollide(Object *other, int myBoxID, int otherBoxID);

};
#endif
