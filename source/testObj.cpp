#include "headers/Object.hpp"
#include <cmath>
#include <iostream>

using namespace std;

class testObj: public Object {

    public:
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
		direction = 1;
	}

	void process(){
		xMove += 1 * (direction);
		yMove -= 1 * (direction);
		if(xMove > 10 || xMove < -10){
			direction *= -1;
		}
		this->x += xMove;
		this->y += yMove;
	
	}


};
