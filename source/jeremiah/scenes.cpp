#include "../headers/Globals.hpp"
#include "scenes.hpp"
#include "globalvars.hpp"
#include <string>

Scene *level1(){

	Scene *gameScene = new Scene(2000,2000);
	
	//Create objects

	//Background
	background *bg = new background(0,0);

    player *p1 = new player(50,50,0,PLAYER,false);

	planet *planet1 = new planet(200,200,0,ENEMY,false);

	planet *planet2 = new planet(1000,400,0,ENEMY,false);
	planet2->setSprite(3);

	asteroid *asteroid1 = new asteroid(1500,600,0,ENEMY,false);

    gameScene->addObject(bg);
	gameScene->addObject(planet2);
	gameScene->addObject(asteroid1);
    gameScene->addObject(p1);
	gameScene->addObject(planet1);


	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,50);
	
	return gameScene;
}

