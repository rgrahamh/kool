#include "headers/Object.hpp"
#include "headers/Globals.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

class testObj2: public Object {

    public:
		int xScale;
		int yScale;
        int xMove;
		int yMove;
		int direction;
		int xSwitch;

		//This code has to be present in all child objects of Object
		testObj2(float x, float y):Object(x,y){
			create();
		}

		void create(){
			xMove = 0;
			yMove = 0;
			xScale = 18;
			yScale = 18;
			direction = 1;
			setSprite((unsigned int)0);
			xSwitch = 1;
			//this->debug=true;
			this->addHitBox(0,0,16,16);
		}

		void process(double delta){
			/*
			xMove += xScale * (direction);
			yMove -= yScale * (direction);
			if(xMove > 10 || xMove < -10){
				direction *= -1;
			}
			this->x += xMove;
			this->y += yMove;
			*/
            delta = delta / 10.0;

            if(Keys::isKeyPressed(Keys::Right)){
                x += delta;
            }
            if(Keys::isKeyPressed(Keys::Left)){
                x -= delta;
            }
            if(Keys::isKeyPressed(Keys::Up)){
                y -= delta;
            }
            if(Keys::isKeyPressed(Keys::Down)){
                y += delta;
            }
		}

        void onCollide(Object *other, int myBoxID, int otherBoxID){
            printf("Colliding!\n");
        }
};
