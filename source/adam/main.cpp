#include <iostream>
#include <string>
#include "../headers/GameEngine.hpp"
#include "scenes.hpp"
#include "gameobjects.hpp"
#include "globalvars.hpp"

int activePlayer = 0;
int currentLevel = 0;
std::function<Scene *()> levelFunc = level1;
std::vector<std::function<Scene *()>> levels = {level1};

std::vector<unsigned int> p1Small = {0,4,3,5,6,7,11,42,43};
std::vector<unsigned int> p2Small = {14,15,16,17,18,19,20,44,45};
std::vector<unsigned int> p1Big = {21,22,23,24,25,26,27,28,29,30};
std::vector<unsigned int> p2Big = {32,33,34,35,36,37,38,39,40,41};
//Setup Players
struct playerData gracin = {3,true,"Gracin",sf::Color::Red,TELEKINESIS,p1Small,p1Big,false};
struct playerData owen = {3,true,"Owen",sf::Color::Green,SUPERSPEED,p2Small,p2Big,false};
struct playerData madison = {3,true,"Madison",sf::Color::Blue,GHOST,p1Small,p1Big,false};

struct playerData players[3] = {gracin,owen,madison};
int playerNum = 3;
//Setup player sprite sets
//Set organization:
//Right standing, left standing, right running, left running, right jumping, left jumping, dead/crouch right, flag1, flag2, crouch left

//Path Strings
std::string characters = "resources/adam/characters/";

//global player dead
bool activeDead = false;

using namespace std;

int main(){

	GameEngine myEngine = *(new GameEngine(600,525,"Super Mario Bros"));

	//Create Scene

	//Create Sprites and format them

	//index 0
	Sprite *mario_standing_right = new Sprite(characters+"mario/small/stand/mStandingSmall.png");

	//index 1
	Sprite *background_sprite = new Sprite("resources/adam/background.jpg");
	background_sprite->setRepeated(true);
	background_sprite->setSize(2000,342);

	//index 2
	Sprite *ground_sprite = new Sprite("resources/adam/ground.png");
	ground_sprite->setRepeated(true);
	ground_sprite->setSize(2000,180);

	//index 3
	Sprite *mario_running_right = new Sprite(characters+"mario/small/run/mSmallRun1.png");
	mario_running_right->addImage(characters+"mario/small/run/mSmallRun2.png");
	mario_running_right->addImage(characters+"mario/small/run/mSmallRun3.png");

	//index 4
	Sprite *mario_standing_left = new Sprite(characters+"mario/small/stand/mStandingSmallL.png");
	
	//index 5
	Sprite *mario_running_left = new Sprite(characters+"mario/small/run/mSmallRunL1.png");
	mario_running_left->addImage(characters+"mario/small/run/mSmallRunL2.png");
	mario_running_left->addImage(characters+"mario/small/run/mSmallRunL3.png");

	//index 6
	Sprite *mario_jumping_right = new Sprite(characters+"mario/small/jump/mSmallJump.png");

	//index 7
	Sprite *mario_jumping_left = new Sprite(characters+"mario/small/jump/mSmallJumpL.png");

	//index 8
	Sprite *block = new Sprite("resources/adam/block.png");

	//index 9
	Sprite *gomba_sprite = new Sprite("resources/adam/enemies/gomba1.png");
	gomba_sprite->addImage("resources/adam/enemies/gomba2.png");

	//index 10
	Sprite *gomba_dead = new Sprite("resources/adam/enemies/gomba_dead.png");

	//index 11
	Sprite *mario_dead = new Sprite(characters+"mario/small/die/mDie.png");

	//index 12
	Sprite *mystery_box = new Sprite("resources/adam/mystery_box/box1.png");
	mystery_box->addImage("resources/adam/mystery_box/box2.png");
	mystery_box->addImage("resources/adam/mystery_box/box3.png");
	mystery_box->addImage("resources/adam/mystery_box/box2.png");

	//index 13
	Sprite *mystery_box_hit = new Sprite("resources/adam/mystery_box/boxHit.png");

	//index 14
	Sprite *luigi_standing_right = new Sprite(characters+"luigi/small/stand/LStandingSmall.png");

	//index 15
	Sprite *luigi_standing_left = new Sprite(characters+"luigi/small/stand/LStandingSmallL.png");

	//index 16
	Sprite *luigi_running_right = new Sprite(characters+"luigi/small/run/LSmallRun1.png");
	luigi_running_right->addImage(characters+"luigi/small/run/LSmallRun2.png");
	luigi_running_right->addImage(characters+"luigi/small/run/LSmallRun3.png");

	//index 17
	Sprite *luigi_running_left = new Sprite(characters+"luigi/small/run/LSmallRunL1.png");
	luigi_running_left->addImage(characters+"luigi/small/run/LSmallRunL2.png");
	luigi_running_left->addImage(characters+"luigi/small/run/LSmallRunL3.png");

	//index 18
	Sprite *luigi_jumping_right = new Sprite(characters+"luigi/small/jump/LSmallJump.png");
	
	//index 19
	Sprite *luigi_jumping_left = new Sprite(characters+"luigi/small/jump/LSmallJumpL.png");

	//index 20
	Sprite *luigi_dead = new Sprite(characters+"luigi/small/die/LSmallDie.png");

	//index 21
	Sprite *mbig_stand_r = new Sprite(characters+"mario/big/stand/mStandingBig.png");
	
	//index 22
	Sprite *mbig_stand_l = new Sprite(characters+"mario/big/stand/mStandingBigL.png");

	//index 23
	Sprite *mbig_run_r = new Sprite(characters+"mario/big/run/mBigRunning1.png");
	mbig_run_r->addImage(characters+"mario/big/run/mBigRunning2.png");
	mbig_run_r->addImage(characters+"mario/big/run/mBigRunning3.png");

	//index 24
	Sprite *mbig_run_l = new Sprite(characters+"mario/big/run/mBigRunningL1.png");
	mbig_run_l->addImage(characters+"mario/big/run/mBigRunningL2.png");
	mbig_run_l->addImage(characters+"mario/big/run/mBigRunningL3.png");

	//index 25
	Sprite *mbig_jump_r = new Sprite(characters+"mario/big/jump/mBigJump.png");

	//index 26
	Sprite *mbig_jump_l = new Sprite(characters+"mario/big/jump/mBigJumpL.png");

	//index 27
	Sprite *mbig_crouch_r = new Sprite(characters+"mario/big/crouch/mBigCrouch.png");

	//index 28
	Sprite *mbig_flag_1 = new Sprite(characters+"mario/big/flag/mBigFlag1.png");

	//index 29
	Sprite *mbig_flag_2 = new Sprite(characters+"mario/big/flag/mBigFlag2.png");

	//index 30
	Sprite *mbig_crouch_l = new Sprite(characters+"mario/big/crouch/mBigCrouchL.png");

	//index 31
	Sprite *mushroom_spr = new Sprite("resources/adam/mushroom.png");

	//index 32
	Sprite *lbig_stand_r = new Sprite(characters+"luigi/big/stand/LStandingBig.png");

	//index 33
	Sprite *lbig_stand_l = new Sprite(characters+"luigi/big/stand/LStandingBigL.png");

	//index 34
	Sprite *lbig_run_r = new Sprite(characters + "luigi/big/run/LBigRunning1.png");
	lbig_run_r->addImage(characters+"luigi/big/run/LBigRunning2.png");
	lbig_run_r->addImage(characters+"luigi/big/run/LBigRunning3.png");

	//index 35
	Sprite *lbig_run_l = new Sprite(characters+"luigi/big/run/LBigRunningL1.png");
	lbig_run_l->addImage(characters+"luigi/big/run/LBigRunningL2.png");
	lbig_run_l->addImage(characters+"luigi/big/run/LBigRunningL3.png");

	//index 36
	Sprite *lbig_jump_r = new Sprite(characters+"luigi/big/jump/LBigJump.png");

	//index 37
	Sprite *lbig_jump_l = new Sprite(characters+"luigi/big/jump/LBigJumpL.png");

	//index 38
	Sprite *lbig_crouch_r = new Sprite(characters+"luigi/big/crouch/LBigCrouch.png");

	//index 39
	Sprite *lbig_flag_1 = new Sprite(characters+"luigi/big/flag/LBigFlag1.png");

	//index 40
	Sprite *lbig_flag_2 = new Sprite(characters+"luigi/big/flag/LBigFlag2.png");

	//index 41
	Sprite *lbig_crouch_l = new Sprite(characters+"luigi/big/crouch/LBigCrouchL.png");

	//index 42
	Sprite *msmall_flag_1 = new Sprite(characters+"mario/small/flag/mSmallFlag1.png");
	
	//index 43
	Sprite *msmall_flag_2 = new Sprite(characters+"mario/small/flag/mSmallFlag2.png");

	//index 44
	Sprite *lsmall_flag_1 = new Sprite(characters+"luigi/small/flag/LSmallFlag1.png");

	//index 45
	Sprite *lsmall_flag_2 = new Sprite(characters+"luigi/small/flag/LSmallFlag2.png");

	//index 46
	Sprite *flagpolesprite = new Sprite("resources/adam/flagpole.png");

	//index 47
	Sprite *flagsprite = new Sprite("resources/adam/flag.png");

	//index 48
	Sprite *metalblock = new Sprite("resources/adam/metalblock.png");

	//index 49
	Sprite *castleSpr = new Sprite("resources/adam/castle.png");

	//index 50
	Sprite *koopa = new Sprite("resources/adam/enemies/koopa1.png");
	koopa->addImage("resources/adam/enemies/koopa2.png");
	
	//index 51
	Sprite *koopaShell = new Sprite("resources/adam/enemies/koopaShell.png");

	//index 52
	Sprite *koopaShellEscape = new Sprite("resources/adam/enemies/koopaShellEscape.png");

	//index 53
	Sprite *koopaLeft = new Sprite("resources/adam/enemies/koopa1L.png");
	koopaLeft->addImage("resources/adam/enemies/koopa2L.png");

	//index 54
	Sprite *dedGomba = new Sprite("resources/adam/enemies/gombaOof.png");

	//index 55
	Sprite *pipe = new Sprite("resources/adam/pipe.png");

	//index 56
	Sprite *breakBlock = new Sprite("resources/adam/breakBlock.png");

	//index 57
	Sprite *pulse = new Sprite("resources/adam/effects/pulse1.png");
	pulse->addImage("resources/adam/effects/pulse2.png");
	pulse->addImage("resources/adam/effects/pulse3.png");
	pulse->addImage("resources/adam/effects/pulse4.png");
	pulse->addImage("resources/adam/effects/pulse5.png");
	pulse->addImage("resources/adam/effects/pulse6.png");
	pulse->addImage("resources/adam/effects/pulse7.png");
	pulse->addImage("resources/adam/effects/pulse8.png");
	pulse->addImage("resources/adam/effects/pulse9.png");
	pulse->addImage("resources/adam/effects/pulse10.png");
	pulse->addImage("resources/adam/effects/pulse11.png");
	pulse->addImage("resources/adam/effects/pulse12.png");
	pulse->addImage("resources/adam/effects/pulse13.png");
	pulse->addImage("resources/adam/effects/pulse14.png");
	pulse->addImage("resources/adam/effects/pulse15.png");
	pulse->addImage("resources/adam/effects/pulse16.png");
	pulse->addImage("resources/adam/effects/pulse17.png");
	pulse->addImage("resources/adam/effects/pulse18.png");
	pulse->addImage("resources/adam/effects/pulse19.png");
	pulse->addImage("resources/adam/effects/pulse20.png");
	pulse->addImage("resources/adam/effects/pulse21.png");
	pulse->addImage("resources/adam/effects/pulse22.png");
	pulse->addImage("resources/adam/effects/pulse23.png");
	pulse->addImage("resources/adam/effects/pulse24.png");
	pulse->addImage("resources/adam/effects/pulse25.png");
	pulse->addImage("resources/adam/effects/pulse26.png");
	pulse->addImage("resources/adam/effects/pulse27.png");
	pulse->addImage("resources/adam/effects/pulse28.png");
	pulse->addImage("resources/adam/effects/pulse29.png");
	pulse->addImage("resources/adam/effects/pulse30.png");

	//Add Scenes to the Engine
	myEngine.addScene(createMenuScene()); //scene ID = 0
	myEngine.addScene(level1()); //gameScene has sceneID=1
	myEngine.addScene(createPreviewScene()); //sceneID=2
	myEngine.addScene(gameoverScene()); //sceneID=3

	//Start Game
	myEngine.startGame();


	return 0;
}
