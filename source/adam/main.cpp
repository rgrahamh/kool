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
	Sprite *mario_standing_right = new Sprite("resources/adam/m_standing_right.png");

	//index 1
	Sprite *background_sprite = new Sprite("resources/adam/background.jpg");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,342);

	//index 2
	Sprite *ground_sprite = new Sprite("resources/adam/ground.png");
	ground_sprite->setRepeated(true);
	ground_sprite->setSize(2000,180);

	//index 3
	Sprite *mario_running_right = new Sprite("resources/adam/m_running_right1.png");
	mario_running_right->addImage("resources/adam/m_running_right2.png");
	mario_running_right->addImage("resources/adam/m_running_right3.png");

	//index 4
	Sprite *mario_standing_left = new Sprite("resources/adam/m_standing_left.png");
	
	//index 5
	Sprite *mario_running_left = new Sprite("resources/adam/m_running_left1.png");
	mario_running_left->addImage("resources/adam/m_running_left2.png");
	mario_running_left->addImage("resources/adam/m_running_left3.png");

	//Create objects
	background *bg = new background(0,0);

	player *p1 = new player(50,50,0,PLAYER,true);

	ground *ground_object = new ground(0,342,0,GROUND,false);

	//Add objects to the scenes
	gameScene->addObject(bg);
	gameScene->addObject(ground_object);
	gameScene->addObject(p1);


	//Add Scenes to the Engine
	myEngine.addScene(gameScene);

	//Create Objects
	myEngine.startGame();


	return 0;
}
