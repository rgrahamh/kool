#include "headers/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;

Scene::Scene(){
	View *tmp = new View(0,0,0,0,800,600); //Hard coded values. Will be changeable later.
	this->addView(tmp);
}

int Scene::addObject(Object *object){
	this->objectList.push_back(object);
	return 0;
}

int Scene::addView(View *view){
	this->viewList.push_back(view);
	return 0;
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
