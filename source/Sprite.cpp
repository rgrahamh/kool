#include "headers/Sprite.hpp"
#include <string>
#include <iostream>
#include "headers/Globals.hpp"

using namespace std;


Sprite::Sprite(std::string path){
	
	this->addImage(path);

	this->xOffset = 0;
	this->yOffset = 0;
	
	Sprite *tmp = this;

	spriteIndex.push_back(tmp);
}

bool Sprite::addImage(std::string filePath){
	sf::Texture img;
	bool result = img.loadFromFile(filePath);
	if(result==true){
		this->images.push_back(img);
		this->imagePaths.push_back(filePath);
	}
	sf::Vector2u tmp = img.getSize();
	setSize(tmp.x,tmp.y);

	return result;

}

sf::Texture Sprite::getImage(unsigned int index){
	if(index >= this->images.size()){
		throw "Error in Sprite::getImage: index too large";
	}
	return this->images[index];
}

std::string Sprite::getImagePath(unsigned int index){
	if(index >= this->imagePaths.size()){
		throw "Error in Sprite::getImagePath: index too large";
	}
	return this->imagePaths[index];
}

void Sprite::setRepeated(bool repeat){
	this->repeated = repeat;
}
void Sprite::setSize(int width, int height){
	this->width = width;
	this->height = height;
}
