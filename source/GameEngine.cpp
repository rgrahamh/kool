#include "headers/GameEngine.hpp"

using namespace std;

GameEngine::GameEngine(int width, int height,string title){
	this->window = new sf::RenderWindow(sf::VideoMode(width,height),title);
	this->winWidth = width;
	this->winHeight = height;
	this->window->setFramerateLimit(60);
}

void GameEngine::startGame(){
	while(this->window->isOpen()){//Main game loop

		//Render
		renderScene();

		//Process key presses and other window events
		while(this->window->pollEvent(this->event)){
			if(this->event.type == sf::Event::Closed){
				this->window->close();
			}

		}

		//Process game objects
		processScene();	

	}
}

void GameEngine::renderScene(){
	//Render
	this->activeScene->render(this->window);
}

void GameEngine::processScene(){
	this->activeScene->process();
}

void GameEngine::endGame(){
	this->window->close();
}

int GameEngine::addScene(Scene *scene){
	View *tmp = new View(0,0,0,0,winWidth,winHeight);
	scene->addView(tmp);
	this->sceneList.push_back(scene);
	if(this->sceneList.size()<2){
		this->activeScene = scene;
	}

	return 0;
}
