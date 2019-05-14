#include "./headers/scenes.hpp"

Scene* createTitleScreen(){
    Scene *scene = new Scene(1600, 900);

    Title* title = new Title(344, 310);

    scene->addObject(title);

    return scene;
}

Scene* createMainGame(){
    stopAllSounds();

    playSound((char*)"./resources/r1/sound/dr-wileys-castle.wav", true);

    Scene *scene  = new Scene(20000, 900);

    //Create the backgound object
    Background* background = new Background(0, 0, 0);

    //Create the barrels
    Background* barrels = new Background(800, 670, 17);
    
    //Create the clouds
    Background* clouds = new Background(0, 0, 18);

    //Create the player
    Player* mman = new Player(50, 500, 0, PLAYER, true);

    //Create the ground
    Ground* ground = new Ground(0, 800, 20, 0, GROUND, false);

    Joe* joe1 = new Joe(980, 752, mman, 0, ENEMY, false);
    
    //Add objects to the scenes
    scene->addObject(background);
    scene->addObject(clouds);
    scene->addObject(barrels);
    scene->addObject(ground);
    scene->addObject(joe1);
    scene->addObject(mman);
    
    //Create additional ground tiles
    Ground* tempGround;
    float groundTiles[][2] = {{256, 736}, {320, 736}, {384, 736}, {384, 672}, {384, 608}, {448, 736}, {448, 672}, {448, 608}, {512, 736}, {576, 736}};

    for(int i = 0; i < (sizeof groundTiles / sizeof groundTiles[0]); i++){
        tempGround = new Ground(groundTiles[i][0], groundTiles[i][1], 15, i, GROUND, false);
        scene->addObject(tempGround);
    }

    float topGround[][2] = {{256, 672}, {320, 672}, {384, 544}, {448, 544}};

    for(int i = 0; i < (sizeof topGround / sizeof topGround[0]); i++){
        tempGround = new Ground(topGround[i][0], topGround[i][1], 16, i, GROUND, false);
        scene->addObject(tempGround);
    }

    scene->scaleAllObjects(2.0, 2.0);

    scene->gravity = 1.0;

    scene->getView(0)->setFollowing(mman, 300, 600);

    return scene;
}
