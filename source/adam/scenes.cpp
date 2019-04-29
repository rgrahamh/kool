#include "scenes.hpp"
#include "globalvars.hpp"
#include <string>

Scene *level1(){

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
	genericText *titleText = new genericText(0,0,-1,0,false);
	titleText->setText(100,150,24,false,"resources/arial.ttf","Super Zelski Bros");

	//Start Prompt
	genericText *promptText = new genericText(0,0,-1,0,false);
	promptText->setText(150,300,18,false,"resources/arial.ttf","Press X to Start");

	//gameTrigger
	gameTrigger *trigger = new gameTrigger(0,0,-1,0,false);

	//Add objects to the scenes
	menuScene->addObject(bg);
	menuScene->addObject(ground_object);
	menuScene->addObject(titleText);
	menuScene->addObject(promptText);
	menuScene->addObject(trigger);

	return menuScene;

}

Scene *createLevelScene(){
	Scene *levelScene = new Scene(600,525);

	//Create Objects
	genericText *lifeText = new genericText(0,0,-1,0,false);
	std::string lifeString;
	if(activePlayer==1){
		lifeString = "Gracin: " + std::to_string(p1Lives); + " lives left.";
	}
	else{
		lifeString = "Owen: " + std::to_string(p2Lives); + " lives left.";
	}
	lifeText->setText(150,150,18,false,"resources/arial.ttf",lifeString);

	//timeTrigger

	//Add objects to the scenes
	levelScene->addObject(lifeText);


	return levelScene;

}
