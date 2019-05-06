#include "game.h"
#include "../headers/Globals.hpp"
#include "../headers/GameEngine.hpp"


void Runner::run()
{

}

background::background(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x,y,collisionLayer,collisionFlags,grav) {
    create();
}

void background::create()
{
    this->collisionLayer = -1;
    setSprite((unsigned int) 0x0);
}

int main(int argc, char **argv, char **evnp)
{
    GameEngine engine = *(new GameEngine(600,600,"Running Simulator 2019"));

    //sprite 0
    Sprite *background_sprite = new Sprite("resources/r2/background.png");
    background_sprite->setRepeated(true);
    background_sprite->setSize(600,600);

    Sprite *runner_standing = new Sprite("resources/r2/runner_standing.png");

    engine.startGame();

    return 0;
}
