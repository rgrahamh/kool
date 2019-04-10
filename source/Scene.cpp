#include "headers/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//The number of clock cycles per millisecond
#define CLOCKS_PER_MS ((float)(CLOCKS_PER_SEC/1000))

using namespace std;

Scene::Scene(){
    this->thisFrame = clock();
}

int Scene::addObject(Object *object){
	this->objectList.push_back(object);
	return 0;
}

int Scene::addView(View *view){
	this->viewList.push_back(view);
	return 0;
}

//process 1 frame of the scene
void Scene::process(){
    this->lastFrame = this->thisFrame;
    thisFrame = clock();
    if(thisFrame >= lastFrame){
        delta = (thisFrame - lastFrame)/CLOCKS_PER_MS;
    } else {
        delta = thisFrame;
    }
	for(unsigned int i = 0; i < this->objectList.size(); i++){
		this->objectList[i]->_process(delta);
	}
}

//render 1 frame of the scene
void Scene::render(sf::RenderWindow *window){

	//Clear the window with the black color
	window->clear(sf::Color::Black);

	//Struct to hold object drawing data
	struct drawData objDraw;
	//Struct to hold position translation information
	struct position translation;
	//Sprite to hold object to draw
	sf::Sprite objSprite;
	//Texture
	sf::Texture sprTexture;

	//Iterate through views
	for(unsigned int i = 0; i < this->viewList.size();i++){
		//cout << "Processing View: " << i << endl;
		//Iterate through objects
		for(unsigned int j = 0; j < this->objectList.size();j++){
			//cout << "Processing Object: " << j << endl;

			//Get data needed to render the object
			objDraw = objectList[j]->_draw();

			//Process View translation
			translation = this->viewList[i]->translate(objDraw.x,objDraw.y);

			objDraw.x = translation.x;
			objDraw.y = translation.y;

			if(objDraw.sprite!=NULL){
				//Draw Sprite
				//Retrieve the image with index imageIndex from the sprite pointed to by the
				//object we are trying to draw
				sprTexture = (objDraw.sprite->getImage(objDraw.imageIndex));
				objSprite.setTexture(sprTexture);
				objSprite.setPosition(objDraw.x,objDraw.y);
				window->draw(objSprite);			
			}
		}
	}
	window->display();

	return;
}
