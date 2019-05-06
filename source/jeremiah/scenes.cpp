#include "../headers/Globals.hpp"
#include "scenes.hpp"
#include <string>

Scene *level1(){

	Scene *gameScene = new Scene(2000,525);
	
	//Create objects

	//Background
	background *bg = new background(0,0);

    player *p1 = new player(50,50,0,PLAYER,false);

    gameScene->addObject(bg);
    gameScene->addObject(p1);

	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,300);
	
	return gameScene;
}

