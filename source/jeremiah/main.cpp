#include <iostream>
#include "../headers/GameEngine.hpp"
#include "game.cpp"

using namespace std;

int main(){

    GameEngine j_engine = *(new GameEngine(800,600,"Space"));

    Scene *gameScene = new Scene(2000,600);

    Sprite *background_sprite = new Sprite("resources/game_space_bg.png");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,342);

    background *bg = new background(0,0);

    gameScene->addObject(bg);

    myEngine.addScene(gameScene);

    myEngine.startGame();


	return 0;
}