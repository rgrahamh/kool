#include "../headers/Globals.hpp"
#include "../headers/GameEngine.hpp"
#include "game.h"
#include "scenes.h"
#include "objects.h"

std:: string resources = "resources/r2/";


using namespace std;

int main(int argc, char **argv, char **evnp)
{
    GameEngine engine = *(new GameEngine(512,512,"Running Simulator 2019"));

    // sprite 0
    Sprite *background_sprite = new Sprite(resources + "background.png");
    background_sprite->setRepeated(true);
    // sprite 1
    Sprite *runner_standing = new Sprite(resources + "runner_standing.png");
    // sprite 2
    Sprite *runner_running = new Sprite(resources + "runner_anims_01.png");
    runner_running->addImage(resources + "runner_anims_02.png");
    runner_running->setSize(64,64);
    // sprite 3
    Sprite *hurdle = new Sprite(resources + "hurdle.png");
    // sprite 4
    Sprite *ground = new Sprite(resources + "ground.png");
    ground->setRepeated(true);
    ground->setSize(8192,ground->height);

    engine.addScene(track());
    engine.startGame();

    return 0;
    
}
