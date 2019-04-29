#include <iostream>
#include "../headers/GameEngine.hpp"
#include "scenes.hpp"
#include "gameobjects.hpp"

using namespace std;

int main(){

	GameEngine myEngine = *(new GameEngine(600,525,"Super Mario Bros"));

	//Create Scene

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

	//index 6
	Sprite *mario_jumping_right = new Sprite("resources/adam/m_jumping_right.png");

	//index 7
	Sprite *mario_jumping_left = new Sprite("resources/adam/m_jumping_left.png");

	//index 8
	Sprite *block = new Sprite("resources/adam/block.png");

	//index 9
	Sprite *gomba_sprite = new Sprite("resources/adam/gomba1.png");
	gomba_sprite->addImage("resources/adam/gomba2.png");

	//index 10
	Sprite *gomba_dead = new Sprite("resources/adam/gomba_dead.png");

	//index 11
	Sprite *mario_dead = new Sprite("resources/adam/mario_dead.png");

	//Add Scenes to the Engine
	myEngine.addScene(createMenuScene());
	myEngine.addScene(createGameScene()); //gameScene has sceneID=0

	//Start Game
	myEngine.startGame();


	return 0;
}
