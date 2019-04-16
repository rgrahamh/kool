#include "headers/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

//The number of clock cycles per millisecond
#define CLOCKS_PER_MS ((float)(CLOCKS_PER_SEC/1000))

using namespace std;

Scene::Scene(int width, int height){
    this->thisFrame = clock();
    this->width = width;
    this->height = height;
	this->id = 0;
}

int Scene::addObject(Object *object){
	this->objectList.push_back(object);
	return 0;
}

int Scene::addView(View *view){
	view->setSceneID(this->id);
	this->viewList.push_back(view);
	return 0;
}

View *Scene::getView(unsigned int index){
	if(index < this->viewList.size()){
		return viewList[index];
	}else{
		return NULL;
	}
}

void Scene::setID(int id){
	this->id = id;
	return;
}

//process 1 frame of the scene
void Scene::process(){
    //Object behavior processing
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
	//Object collision processing
	for(unsigned int i = 0; i < this->objectList.size(); i++){
		//Check each hitbox for each object
		//Process collisions by calling this->objectList[i]->onCollide()
	}
	//View processing
	for(unsigned int i = 0; i < this->viewList.size(); i++){
		this->viewList[i]->_process(delta);
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
	//HitBox list
	std::vector<HitBox *> hBoxes;
	//Debug box
	sf::RectangleShape rectangle;
	

	//Iterate through views
	for(unsigned int i = 0; i < this->viewList.size();i++){
		//cout << "Processing View: " << i << endl;
		//Iterate through objects
		for(unsigned int j = 0; j < this->objectList.size();j++){

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
				objSprite.setTexture(sprTexture,true);
				objSprite.setPosition(objDraw.x,objDraw.y);
				//Debug: Draw HitBoxes
				if(objDraw.drawHitBoxes==true){
					hBoxes = objectList[j]->getHitBoxes();
					for(unsigned int k = 0; k < hBoxes.size(); k++){
						rectangle.setSize(sf::Vector2f(hBoxes[k]->width,hBoxes[k]->height));
						rectangle.setOutlineColor(sf::Color::Red);
						rectangle.setFillColor(sf::Color::Transparent);
						rectangle.setOutlineThickness(2);
						rectangle.setPosition(objectList[j]->x+hBoxes[k]->offsetX,objectList[j]->y+hBoxes[k]->offsetY);

						window->draw(rectangle);
					}
				}
				//Make sure the object sprite is the last thing we draw, so that it is at the foreground.
				window->draw(objSprite);
			}
		}
	}
	window->display();

	return;
}
