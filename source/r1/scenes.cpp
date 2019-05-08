#include "./headers/scenes.hpp"

Scene* createMainGame(){
    Scene *scene  = new Scene(3000, 900);

    //Create the backgound object
    Background* background = new Background(0, 0);

    //Create the barrels
    Background* barrels = new Background(800, 600);

    //Create the player
    Player* mman = new Player(50, 600, 0, PLAYER, true);

    //Create the ground
    Ground* ground = new Ground(0, 800, 0, GROUND, false);

    //Add objects to the scenes
    scene->addObject(background);
    scene->addObject(barrels);
    scene->addObject(ground);
    scene->addObject(mman);

    scene->scaleAllObjects(1.5, 1.5);

    scene->getView(0)->setFollowing(mman, 300, 600);

    return scene;
}
