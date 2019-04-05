#include "headers/Scene.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

Scene::Scene(){
	View *tmp = new View(0,0,0,0,800,600);
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
void Scene::render(sf::RenderWindow *window){//FIXME

	//Clear the window with the black color
	window->clear(sf::Color::Black);

	//Struct to hold object drawing data
	struct drawData objDraw;
	//Iterate through views
	for(unsigned int i = 0; i < this->viewList.size();i++){
		//cout << "Processing View: " << i << endl;
		//Iterate through objects
		for(unsigned int j = 0; j < this->objectList.size();j++){
			//cout << "Processing Object: " << j << endl;

			//Get data needed to render the object
			objDraw = objectList[i]->_draw();

			if(objDraw.sprite!=NULL){
				//Draw Sprite
			}
		}
	}
	window->display();

	return;
}
