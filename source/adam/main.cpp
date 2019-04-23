#include <iostream>
#include "../headers/GameEngine.hpp"
#include "gameobjects.cpp"

using namespace std;

int main(){

	GameEngine myEngine = *(new GameEngine(800,600,"Super Mario Bros"));

	//Create Scene
	Scene *gameScene = new Scene(2000,600);

	//Create Sprites and format them

	//index 0
	Sprite *mario = new Sprite("resources/adam/m_standing_right.png");

	//index 1
	Sprite *background_sprite = new Sprite("resources/adam/background.jpg");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,342);

	//index 2
	Sprite *ground_sprite = new Sprite("resources/adam/ground.png");
	ground_sprite->setRepeated(true);
	ground_sprite->setSize(2000,180);

	//Create objects
	background *bg = new background(0,0);

	player *p1 = new player(50,50,0,PLAYER,true);

	ground *ground_object = new ground(0,342,0,GROUND,false);

	//Add objects to the scenes
	gameScene->addObject(bg);
	gameScene->addObject(ground_object);
	gameScene->addObject(p1);

	myEngine.addScene(gameScene);

	//Create Objects
	myEngine.startGame();


	return 0;
}
