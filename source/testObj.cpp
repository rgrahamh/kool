#include "headers/Object.hpp"
#include "headers/Globals.hpp"
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
		int xSwitch;

		//This code has to be present in all child objects of Object
		testObj(float x, float y):Object(x,y){
			create();
		}

		void create(){
			xMove = 0;
			yMove = 0;
			xScale = (rand() % 6);
			yScale = (rand() % 6);
			direction = 1;
			setSprite((unsigned int)0);
			xSwitch = 1;
		}

		void process(double delta){
			cout << "---PROCESSING" << endl;
			xMove += xScale * (direction);
			yMove -= yScale * (direction);
			if(xMove > 10 || xMove < -10){
				direction *= -1;
			}
			this->x += xMove;
			this->y += yMove;

			if(Keys::isKeyPressed(Keys::X) && xSwitch==0){
				testObj *tmp = new testObj(600,200);
				xSwitch = 1;
				createObject(tmp);
			}
		
		}


};
