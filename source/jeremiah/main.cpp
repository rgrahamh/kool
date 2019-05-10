#include <iostream>
#include <string>
#include "../headers/GameEngine.hpp"
#include "scenes.hpp"
#include "gameobjects.hpp"
#include "globalvars.hpp"

using namespace std;

int main(){

    GameEngine myEngine = *(new GameEngine(600,525,"Space"));

//index 0 
    Sprite *spaceship = new Sprite("resources/custom2.png");

//index 1
    Sprite *planet = new Sprite("resources/planet.png");


//index2
    Sprite *background_sprite = new Sprite("resources/space_bg2.jpg");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,2000);

//index 3
    Sprite *planet2 = new Sprite("resources/planet2.png");

//index 4
    Sprite *asteroid = new Sprite("resources/asteroid.jpg");

    //Add Scenes to the Engine
    myEngine.addScene(level1()); //gameScene has sceneID=1

	//Start Game
	myEngine.startGame();

return 0;
}