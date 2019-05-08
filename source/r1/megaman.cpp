#include "../headers/GameEngine.hpp"
#include "./headers/scenes.hpp"
#include "./headers/gameobjects.hpp"

std::string MMAN_PATH = "./resources/r1/megaman/";
std::string GROUND_PATH = "./resources/r1/ground/";
std::string BGROUND_PATH = "./resources/r1/background/";

int main(int argc, char* argv){
    //Creating the game engine
	GameEngine kool = *(new GameEngine(1600,900,"Kool Mega Man!"));

    //Create this as just a block of dark blue
    //SPRITE IDX = 0
    Sprite *background_sprite = new Sprite(BGROUND_PATH + "background.png");
    background_sprite->setRepeated(true);
    //TODO: Change this when I actually decide on stage size
    background_sprite->setSize(20000, 900);

    //Creating Mega Man's sprites
    //SPRITE IDX = 1
    Sprite *mman_stand_l = new Sprite(MMAN_PATH + "mman_stand_l.png");
    mman_stand_l->addImage(MMAN_PATH + "mman_blink_l.png");

    //SPRITE IDX = 2
    Sprite *mman_stand_r = new Sprite(MMAN_PATH + "mman_stand_r.png");
    mman_stand_r->addImage(MMAN_PATH + "mman_blink_r.png");

    //SPRITE IDX = 3
    Sprite *mman_run_l = new Sprite(MMAN_PATH + "mman_run_l_1.png");
    mman_run_l->addImage(MMAN_PATH + "mman_run_l_2.png");
    mman_run_l->addImage(MMAN_PATH + "mman_run_l_3.png");

    //SPRITE IDX = 4
    Sprite *mman_run_r = new Sprite(MMAN_PATH + "mman_run_r_1.png");
    mman_run_r->addImage(MMAN_PATH + "mman_run_r_2.png");
    mman_run_r->addImage(MMAN_PATH + "mman_run_r_3.png");

    //SPRITE IDX = 5
    Sprite *mman_shoot_run_l = new Sprite(MMAN_PATH + "mman_shoot_run_l_1.png");
    mman_shoot_run_l->addImage(MMAN_PATH + "mman_shoot_run_l_2.png");
    mman_shoot_run_l->addImage(MMAN_PATH + "mman_shoot_run_l_3.png");

    //SPRITE IDX = 6
    Sprite *mman_shoot_run_r = new Sprite(MMAN_PATH + "mman_shoot_run_r_1.png");
    mman_shoot_run_r->addImage(MMAN_PATH + "mman_shoot_run_r_2.png");
    mman_shoot_run_r->addImage(MMAN_PATH + "mman_shoot_run_r_3.png");

    //SPRITE IDX = 7
    Sprite *mman_jump_l = new Sprite(MMAN_PATH + "mman_jump_l.png");

    //SPRITE IDX = 8
    Sprite *mman_jump_r = new Sprite(MMAN_PATH + "mman_jump_r.png");

    //SPRITE IDX = 9
    Sprite *mman_hurt_l = new Sprite(MMAN_PATH + "mman_hurt_l.png");

    //SPRITE IDX = 10
    Sprite *mman_hurt_r = new Sprite(MMAN_PATH + "mman_hurt_r.png");

    //SPRITE IDX = 11
    Sprite *bottom_ground_sprite = new Sprite(GROUND_PATH + "bottom_ground_tile.png");
    bottom_ground_sprite->setRepeated(true);
    bottom_ground_sprite->setSize(2000, 900);

    //SPRITE IDX = 12
    Sprite *top_ground_sprite = new Sprite(GROUND_PATH + "top_ground_tile.png");
    top_ground_sprite->setRepeated(true);

    //Adding scenes to the game
    kool.addScene(createMainGame());

    //Starting the engine
    kool.startGame();

    return 0;
}
