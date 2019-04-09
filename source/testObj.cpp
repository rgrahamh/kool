#include "headers/Object.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class testObj: public Object {

    public:
	int xScale;
	int yScale;
    	int xMove;
	int yMove;
	int direction;

	//This code has to be present in all child objects of Object
	testObj(int x, int y):Object(x,y){
	    create();
	}

	void create(){
		xMove = 0;
		yMove = 0;
		xScale = (rand() % 6);
		yScale = (rand() % 6);
		direction = 1;
	}

	void process(){
		xMove += xScale * (direction);
		yMove -= yScale * (direction);
		if(xMove > 10 || xMove < -10){
			direction *= -1;
		}
		this->x += xMove;
		this->y += yMove;
	
	}


};
