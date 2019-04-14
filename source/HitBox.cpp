#include "headers/HitBox.hpp"


HitBox::HitBox(int offsetX, int offsetY, int width, int height, double ttl){
	
    	this->offsetX = offsetX;
	this->offsetY = offsetY;
	
	this->width = width;
	this->height = height;

	this->ttl = ttl;

}

double HitBox::decTime(double delta){ //FIXME Pretty sure I'm not decremening the ttl correctly.
	if(this->ttl > 0){
		this->ttl -= 1;
	}
	return this->ttl;
}
