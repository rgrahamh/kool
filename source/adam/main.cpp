#include <iostream>
#include "../headers/GameEngine.hpp"
#include "gameobjects.cpp"

using namespace std;

int main(){

	GameEngine myEngine = *(new GameEngine(600,525,"Super Mario Bros"));

	//Create Scene
	Scene *gameScene = new Scene(2000,525);

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

	//Create objects

	//Background
	background *bg = new background(0,0);

	//Player
	player *p1 = new player(50,50,0,PLAYER,true);

	//Ground
	ground *ground_object = new ground(0,342,0,GROUND,false);

	//Add objects to the scenes
	gameScene->addObject(bg);
	gameScene->addObject(ground_object);
	gameScene->addObject(p1);
	
	//Blocks
	Block *blockTmp;
	float blocks[5][2] = {{200,480},{214,480},{228,466},{260,454},{400,480}};
	for(unsigned int i = 0; i < (sizeof(blocks)/sizeof(blocks[0])); i++){
		blockTmp = new Block(blocks[i][0],blocks[i][1],0,GROUND,false);
		gameScene->addObject(blockTmp);
	}

	//Gombas
	gomba *gombaTmp;
	float gombas[2][2] = {{300,200},{325,250}};
	for(unsigned int i = 0; i < (sizeof(gombas)/sizeof(gombas[0]));i++){
		gombaTmp = new gomba(gombas[i][0],gombas[i][1],0,ENEMY,true);
		gameScene->addObject(gombaTmp);
	}
	


	//Add Scenes to the Engine
	myEngine.addScene(gameScene);

	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,600);

	//Start Game
	myEngine.startGame();


	return 0;
}
