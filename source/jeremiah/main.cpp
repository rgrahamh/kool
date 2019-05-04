#include <iostream>
#include <string>
#include "../headers/GameEngine.hpp"
#include "scenes.hpp"
#include "gameobjects.hpp"

using namespace std;

int main(){

    GameEngine myEngine = *(new GameEngine(600,525,"Space"));

    Sprite *spaceship = new Sprite("resources/dolphin.png");

    Sprite *background_sprite = new Sprite("resources/space_bg2.jpg");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,1000);

    //Add Scenes to the Engine
    myEngine.addScene(level1()); //gameScene has sceneID=1

	//Start Game
	myEngine.startGame();

return 0;
}