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

    Scene *scene  = new Scene(6000, 900);

    //Create the backgound object
    Background* background = new Background(0, 0, 0);

    //Create the barrels
    Background* barrels = new Background(800, 670, 17);
    
    //Create the clouds
    Background* clouds = new Background(0, 0, 18);

    //Create the player
    Player* mman = new Player(50, 0, 0, PLAYER, true);

    //Create the ground
    Ground* start_ground = new Ground(0, 800, 20, 0, GROUND);

    Ground* end_ground = new Ground(4512, 800, 20, 0, GROUND);

    Joe* joe1 = new Joe(980, 752, mman, 0, ENEMY, false);
    Joe* joe2 = new Joe(2060, 752, mman, 0, ENEMY, false);

    Chicken* chicken = new Chicken(5500, 722);
    
    //Add objects to the scenes
    scene->addObject(background);
    scene->addObject(clouds);
    scene->addObject(barrels);
    scene->addObject(start_ground);
    scene->addObject(end_ground);
    scene->addObject(joe1);
    scene->addObject(joe2);
    scene->addObject(chicken);
    scene->addObject(mman);
    
    //Create additional ground tiles
    Ground* tempGround;
    float groundTiles[][2] = {{256, 736}, {320, 736}, {384, 736}, {384, 672}, {384, 608}, {448, 736}, {448, 672}, {448, 608}};
    for(int i = 0; i < (sizeof groundTiles / sizeof groundTiles[0]); i++){
        tempGround = new Ground(groundTiles[i][0], groundTiles[i][1], 15, i, GROUND, false);
        scene->addObject(tempGround);
    }

    float columns[][2] = {{3328, 746}, {3656, 682}, /*{4256, 672}, {4384, 608},*/{4000, 608}, {4128, 608}, {4256, 480}, {4384, 352}, {5744, 352}, {5872, 480}};
    for(int i = 0; i < (sizeof columns / sizeof columns[0]); i++){
        tempGround = new Ground(columns[i][0], columns[i][1], 27, i, GROUND, false);
        scene->addObject(tempGround);
    }

    float topGround[][2] = {{256, 672}, {320, 672}, {384, 544}, {448, 544}, {512, 736}, {576, 736}, {3328, 736},
                            {3392, 736}, {3656, 672}, {3720, 672},
                            {4256, 480}, {4320, 480}, {4384, 352}, {4448, 352},
                            {5744, 352}, {5808, 352}, {5872, 480}, {5936, 480}};
    for(int i = 0; i < (sizeof topGround / sizeof topGround[0]); i++){
        tempGround = new Ground(topGround[i][0], topGround[i][1], 16, i, GROUND, false);
        scene->addObject(tempGround);
    }

    scene->scaleAllObjects(2.0, 2.0);

    scene->gravity = 1.0;

    scene->getView(0)->setFollowing(mman, 300, 600);

    return scene;
}
