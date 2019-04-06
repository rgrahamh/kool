#include "headers/Sprite.hpp"
#include <string>
#include <iostream>

using namespace std;

Sprite::Sprite(std::string path){
	
	this->addImage(path);

	this->xOffset = 0;
	this->yOffset = 0;
}

bool Sprite::addImage(std::string filePath){
	sf::Texture img;
	bool result = img.loadFromFile(filePath);
	if(result==true){
		this->images.push_back(img);
		this->imagePaths.push_back(filePath);
	}

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
