#include "../headers/GameEngine.hpp"
#include "./headers/scenes.hpp"
#include "./headers/gameobjects.hpp"

std::string MMAN_PATH = "./resources/r1/megaman/";
std::string GROUND_PATH = "./resources/r1/ground/";
std::string BGROUND_PATH = "./resources/r1/background/";
std::string SHARED_PATH = "./resources/r1/shared/";
std::string ENEMY_PATH = "./resources/r1/enemies/";

int main(int argc, char** argv){
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
    //mman_stand_l->addImage(MMAN_PATH + "mman_blink_l.png");

    //SPRITE IDX = 2
    Sprite *mman_stand_r = new Sprite(MMAN_PATH + "mman_stand_r.png");
    //mman_stand_r->addImage(MMAN_PATH + "mman_blink_r.png");
    
    //SPRITE IDX = 3
    Sprite *mman_shoot_l = new Sprite(MMAN_PATH + "mman_shoot_l.png");

    //SPRITE IDX = 4
    Sprite *mman_shoot_r = new Sprite(MMAN_PATH + "mman_shoot_r.png");

    //SPRITE IDX = 5
    Sprite *mman_run_l = new Sprite(MMAN_PATH + "mman_run_l_1_24.png");
    mman_run_l->addImage(MMAN_PATH + "mman_run_l_2_24.png");
    mman_run_l->addImage(MMAN_PATH + "mman_run_l_3_24.png");
    mman_run_l->setRepeated(false);

    //SPRITE IDX = 6
    Sprite *mman_run_r = new Sprite(MMAN_PATH + "mman_run_r_1_24.png");
    mman_run_r->addImage(MMAN_PATH + "mman_run_r_2_24.png");
    mman_run_r->addImage(MMAN_PATH + "mman_run_r_3_24.png");
    mman_run_r->setRepeated(false);

    //SPRITE IDX = 7
    Sprite *mman_shoot_run_l = new Sprite(MMAN_PATH + "mman_shoot_run_l_1.png");
    mman_shoot_run_l->addImage(MMAN_PATH + "mman_shoot_run_l_2.png");
    mman_shoot_run_l->addImage(MMAN_PATH + "mman_shoot_run_l_3.png");

    //SPRITE IDX = 8
    Sprite *mman_shoot_run_r = new Sprite(MMAN_PATH + "mman_shoot_run_r_1.png");
    mman_shoot_run_r->addImage(MMAN_PATH + "mman_shoot_run_r_2.png");
    mman_shoot_run_r->addImage(MMAN_PATH + "mman_shoot_run_r_3.png");

    //SPRITE IDX = 9
    Sprite *mman_jump_l = new Sprite(MMAN_PATH + "mman_jump_l.png");

    //SPRITE IDX = 10
    Sprite *mman_jump_r = new Sprite(MMAN_PATH + "mman_jump_r.png");
    
    //SPRITE IDX = 11
    Sprite *mman_jump_shoot_l = new Sprite(MMAN_PATH + "mman_jump_shoot_l.png");

    //SPRITE IDX = 12
    Sprite *mman_jump_shoot_r = new Sprite(MMAN_PATH + "mman_jump_shoot_r.png");

    //SPRITE IDX = 13
    Sprite *mman_hurt_l = new Sprite(MMAN_PATH + "mman_hurt_l.png");
    
    //SPRITE IDX = 14
    Sprite *mman_hurt_r = new Sprite(MMAN_PATH + "mman_hurt_r.png");

    //SPRITE IDX = 15
    Sprite *bottom_ground_sprite = new Sprite(GROUND_PATH + "bottom_ground_tile.png");
    bottom_ground_sprite->setRepeated(true);

    //SPRITE IDX = 16
    Sprite *top_ground_sprite = new Sprite(GROUND_PATH + "top_ground_tile.png");

    //SPRITE IDX = 17
    Sprite *barrels = new Sprite(BGROUND_PATH + "barrels.png");
    
    //SPRITE IDX = 18
    Sprite *clouds = new Sprite(BGROUND_PATH + "clouds.png");
    clouds->setRepeated(true);
    clouds->setSize(20000, 40);

    //SPRITE IDX = 19
    Sprite *bullet_sprite = new Sprite(SHARED_PATH + "bullet.png");
    
    //SPRITE IDX = 20
    Sprite *ground_sprite = new Sprite(GROUND_PATH + "bottom_ground_tile.png");
    ground_sprite->setRepeated(true);
    ground_sprite->setSize(1600, 200);

    //SPRITE IDX = 21
    Sprite *joe_shield_l = new Sprite(ENEMY_PATH + "joe_shield_l.png");

    //SPRITE IDX = 22
    Sprite *joe_shield_r = new Sprite(ENEMY_PATH + "joe_shield_r.png");

    //SPRITE IDX = 23
    Sprite *joe_shoot_l = new Sprite(ENEMY_PATH + "joe_shoot_l.png");

    //SPRITE IDX = 24
    Sprite *joe_shoot_r = new Sprite(ENEMY_PATH + "joe_shoot_r.png");

    //SPRITE IDX = 25
    Sprite *transparent = new Sprite(SHARED_PATH + "transparent.png");

    //SPRITE IDX = 26
    Sprite *title = new Sprite(SHARED_PATH + "title_screen.png");

    //SPRITE IDX = 27
    Sprite *column_sprite = new Sprite(GROUND_PATH + "bottom_ground_tile.png");
    column_sprite->setRepeated(true);
    column_sprite->setSize(64, 400);

    //SPRITE IDX = 28
    Sprite *chicken_l = new Sprite(ENEMY_PATH + "chicken_l_1.png");
    chicken_l->addImage(ENEMY_PATH + "chicken_l_2_39.png");
    chicken_l->addImage(ENEMY_PATH + "chicken_l_3_39.png");

    //SPRITE IDX = 29
    Sprite *chicken_r = new Sprite(ENEMY_PATH + "chicken_r_1.png");
    chicken_r->addImage(ENEMY_PATH + "chicken_r_2_39.png");
    chicken_r->addImage(ENEMY_PATH + "chicken_r_3_39.png");

    //SPRITE IDX = 30
    Sprite *beam = new Sprite(MMAN_PATH + "mman_warp.png");

    //SPRITE IDX = 31
    Sprite *assemble = new Sprite(MMAN_PATH+ "mman_assemble_1.png");
    assemble->addImage(MMAN_PATH + "mman_assemble_2.png");
    assemble->addImage(MMAN_PATH + "mman_assemble_3.png");

    //SPRITE IDX = 32
    Sprite *disassemble = new Sprite(MMAN_PATH + "mman_assemble_1.png");
    disassemble->addImage(MMAN_PATH + "mman_assemble_2.png");
    disassemble->addImage(MMAN_PATH + "mman_assemble_3.png");
    
    //SPRITE IDX = 33
    Sprite *pickup_sprite = new Sprite(SHARED_PATH + "pickup.png");

    //SPRITE IDX = 34
    Sprite *death_sprite = new Sprite(MMAN_PATH + "die_1.png");
    death_sprite->addImage(MMAN_PATH + "die_2.png");
    death_sprite->addImage(MMAN_PATH + "die_3.png");
    death_sprite->addImage(MMAN_PATH + "die_4.png");
    death_sprite->addImage(MMAN_PATH + "die_5.png");

    //Adding scenes to the game
    kool.addScene(createTitleScreen());
    kool.addScene(createMainGame());
    kool.addScene(createGameOver());
    kool.addScene(createVictoryScreen());

    playSound((char*)"./resources/r1/sound/title-screen.wav", true);

    //Starting the engine
    kool.startGame();

    return 0;
}
