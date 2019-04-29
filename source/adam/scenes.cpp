#include "scenes.hpp"

Scene *createGameScene(){

	Scene *gameScene = new Scene(2000,525);
	
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

	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,600);
	
	return gameScene;

}

Scene *createMenuScene(){

	Scene *menuScene = new Scene(600,525);

	//Create Objects
	background *bg = new background(0,0);

	//Ground
	ground *ground_object = new ground(0,342,0,GROUND,false);

	//Menu Text
	genericText *titleText = new genericText(0,0,-1,PLAYER,false);
	titleText->setText(200,200,24,false,"resources/arial.ttf","Super Mario Bros.");

	//Add objects to the scenes
	menuScene->addObject(bg);
	menuScene->addObject(ground_object);
	menuScene->addObject(titleText);

	return menuScene;

}
