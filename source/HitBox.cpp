#include "headers/HitBox.hpp"


HitBox::HitBox(int offsetX, int offsetY, int width, int height, double ttl){
	
    	this->offsetX = offsetX;
	this->offsetY = offsetY;
	
	this->width = width;
	this->height = height;

	this->ttl = ttl;
	if(ttl < 0.0){
		this->infinite = true;
	}else{
		this->infinite = false;
	}

}

double HitBox::decTime(double delta){ //FIXME Pretty sure I'm not decremening the ttl correctly.
	if(this->infinite == false){
		this->ttl -= delta;
	}
	return this->ttl;
}
