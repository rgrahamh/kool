#include "headers/GameEngine.hpp"

GameEngine::GameEngine(){
	this->window = new sf::RenderWindow(sf::VideoMode(800,600),"Kool Engine");
	this->window->setFramerateLimit(60);
}

void GameEngine::startGame(){
	while(this->window->isOpen()){//Main game loop

		//Render
		this->activeScene->render(this->window);

		//Process key presses and other window events
		while(this->window->pollEvent(this->event)){
			if(this->event.type == sf::Event::Closed){
				this->window->close();
			}

		}

		//Process game objects
		

	}
}

void GameEngine::endGame(){
	this->window->close();
}

int GameEngine::addScene(Scene *scene){
	this->sceneList.push_back(scene);
	if(this->sceneList.size()<2){
		this->activeScene = scene;
	}

	return 0;
}
