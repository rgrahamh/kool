#include "../headers/Globals.hpp"
#include "scenes.hpp"
#include "globalvars.hpp"
#include <string>

Scene *level2(){

	Scene *gameScene = new Scene(3000,520);
	
	//Create objects
	//Backmost background
	background *bg2 = new background(0,0);
	bg2->setSprite((unsigned int)58);
	bg2->sprite_width = 3000;
	bg2->sprite_height = 520;

	//Background
	background *bg = new background(0,0);
	spriteIndex[1]->setSize(gameScene->width,342);
	
	//Flag post
	flagpole *fp = new flagpole(gameScene->width-320,326,0,GOAL,false);

	//Flag
	aFlag *theFlag = new aFlag(fp->x-3,fp->y+20,0,0,false);

	fp->myFlag = theFlag;

	//Castle
	castle *cstl = new castle(gameScene->width-200,415,0,0x60,false);

	//Player
	player *p1 = new player(50,452,0,PLAYER,true);

	//Ground
	ground *ground_object = new ground(0,342,0,GROUND,false);
	ground_object->sprite_width=248;

	//Ground
	ground *ground_object2 = new ground(296,342,0,GROUND,false);
	ground_object2->sprite_width=1712-296;

	//Ground
	ground *ground_object3 = new ground(1962,342,0,GROUND,false);
	ground_object3->sprite_width = 1038;

	//Add objects to the scenes
	gameScene->addObject(bg2);
	gameScene->addObject(bg);
	gameScene->addObject(ground_object);
	gameScene->addObject(ground_object2);
	gameScene->addObject(ground_object3);
	gameScene->addObject(theFlag);
	gameScene->addObject(fp);
	gameScene->addObject(cstl);
	gameScene->addObject(p1);
	
	//Blocks
	Block *blockTmp;
	float blocks[][2] ={{29,376},{45,392},{61,408},{75,424},{91,440},
			    {914,430},{930,430},
			    {1026,430},{1042,430},{1058,430},
			    {1288,430},{1304,430},{1352,430},{1368,430},{1384,430},{1400,430},
			    {1400,446},{1400,430},{1400,414},{1400,398},{1400,382},{1400,366},
			};
	for(unsigned int i = 0; i < (sizeof(blocks)/sizeof(blocks[0])); i++){
		blockTmp = new Block(blocks[i][0],blocks[i][1],0,GROUND,false);
		gameScene->addObject(blockTmp);
	}
	//metal blocks
	metalBlock *mBlockTmp;
	float startX;
	float startY;
	float mBlocks[][2] = {{1074,430},{1074,446},{1074,462},{1074,478},{1464,478},
						  {898,430},{1650,398},{1634,398},{1618,398},{1602,398},
						  {1698,350},{1714,350},{1730,350},{1746,350},{1762,350},
						  {1826,494},{1842,494},{1858,494},{1874,494},
						  {1858,350},{1874,350},{1890,350},{1906,350},{1922,350},
						  {2000,478}
						 };
	for(unsigned int i = 0; i < (sizeof(mBlocks)/sizeof(mBlocks[0])); i++){
		mBlockTmp = new metalBlock(mBlocks[i][0],mBlocks[i][1],0,GROUND,false);
		gameScene->addObject(mBlockTmp);
	}

	//Ascending stairs
	startX = 200;
	startY = 494;
	for(unsigned int i = 0; i < 3; i++){
		for(unsigned int j = 0; j < i+1; j++){
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}
	//Descending stairs
	startX = startX+96;
	for(int i = 2; i > -1; i--){
		for(int j = 0; j < 3-i; j++){
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}
	//Ascending stairs
	startX = 1224;
	for(unsigned int i = 0; i < 4; i++){
		for(unsigned int j = 0; j < i+1; j++){
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}
	//Ascending stairs
	startX = 770;
	for(unsigned int i = 0; i < 3; i++){
		for(unsigned int j = 0; j < i+1; j++){
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}
	//Ascending stairs
	startX = 1664;
	for(unsigned int i = 0; i < 3; i++){
		for(unsigned int j = 0; j < i+1; j++){
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}
	//Ceiling	
	float ceilingStart = 0;
	unsigned int ceilingLength = 48;
	for(unsigned int i = 0; i < ceilingLength; i++){
		mBlockTmp = new metalBlock(ceilingStart+(16*i),325,0,GROUND,false);
		gameScene->addObject(mBlockTmp);
	}

	startX = gameScene->width-590;
	startY = 494;
	//Final flag stairs
	for(unsigned int i = 0; i < 9; i++){
		for(unsigned int j = 0; j < i+1; j++){
			if(j > 8){
				j = 8;
			}
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}

	//Mystery Boxes
	MysteryBox *mysteryTmp;
	
	float mysteryBoxes[][2] = {{978,430}};
	for(unsigned int i = 0; i < (sizeof(mysteryBoxes)/sizeof(mysteryBoxes[0])); i++){
		mysteryTmp = new MysteryBox(mysteryBoxes[i][0],mysteryBoxes[i][1],0,GROUND,false);
		gameScene->addObject(mysteryTmp);
	}
	
	
	//Pipes
	staticPipe *staticPipeTmp;
	float staticPipes[][2] = {{2300,462}};
	for(unsigned int i = 0; i < (sizeof(staticPipes)/sizeof(staticPipes[0])); i++){
		staticPipeTmp = new staticPipe(staticPipes[i][0],staticPipes[i][1],0,GROUND,false);
		gameScene->addObject(staticPipeTmp);
	}
	
	//Gombas
	
	gomba *gombaTmp;
	float gombas[][2] = {{190,305},{400,452},{460,452},{510,452},{560,452},{1288,452},{1336,452},
	                     {1368,452},{1400,452},{1432,452},{2096,452},{2116,452},{2132,452},
						 {2148,452},{2164,452},{2196,452},{2216,452},{2232,452},{2248,452},
						 {2264,452}
			    };
	for(unsigned int i = 0; i < (sizeof(gombas)/sizeof(gombas[0]));i++){
		gombaTmp = new gomba(gombas[i][0],gombas[i][1],0,ENEMY,true);
		gameScene->addObject(gombaTmp);
	}
	//koopas
	koopa *koopaTmp;
	float koopas[][2] = {{50,305},{125,305},{930,398},{1042,398},{1714,334},{1842,474},{1890,334},{1634,378}};
	for(unsigned int i = 0; i < (sizeof(koopas)/sizeof(koopas[0]));i++){
		koopaTmp = new koopa(koopas[i][0],koopas[i][1],0,ENEMY,true);
		gameScene->addObject(koopaTmp);
	}
	

	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,600);
	
	return gameScene;
}
Scene *level1(){

	Scene *gameScene = new Scene(2200,520);
	
	//Create objects

	//Background
	background *bg = new background(0,0);
	spriteIndex[1]->setSize(2500,342);
	
	//Flag post
	flagpole *fp = new flagpole(1880,326,0,GOAL,false);

	//Flag
	aFlag *theFlag = new aFlag(fp->x-3,fp->y+20,0,0,false);

	fp->myFlag = theFlag;

	//Castle
	castle *cstl = new castle(2000,415,0,0x60,false);

	//Player
	player *p1 = new player(50,450,0,PLAYER,true);

	//Ground
	ground *ground_object = new ground(0,342,0,GROUND,false);
	spriteIndex[2]->setSize(2500,180);

	//Add objects to the scenes
	gameScene->addObject(bg);
	gameScene->addObject(ground_object);
	gameScene->addObject(theFlag);
	gameScene->addObject(fp);
	gameScene->addObject(cstl);
	gameScene->addObject(p1);
	
	//Blocks
	Block *blockTmp;
	float blocks[18][2] = {{98,438},{114,438},{130,438},
						  {720,452},{734,452},{748,452},{776,410},{790,410},{804,410},
						  {1100,438},{1116,438},{1132,438},
						  {1200,394},{1216,394},{1232,394},
						  {1300,438},{1316,438},{1332,438}
						 };
	for(unsigned int i = 0; i < (sizeof(blocks)/sizeof(blocks[0])); i++){
		blockTmp = new Block(blocks[i][0],blocks[i][1],0,GROUND,false);
		gameScene->addObject(blockTmp);
	}
	//metal blocks
	metalBlock *mBlockTmp;
	float startX = 1610;
	float startY = 494;
	for(unsigned int i = 0; i < 9; i++){
		for(unsigned int j = 0; j < i+1; j++){
			if(j > 8){
				j = 8;
			}
			mBlockTmp = new metalBlock(startX+(16*i),startY-(16*(j+1)),0,GROUND,false);
			gameScene->addObject(mBlockTmp);
		}
	}

	//Mystery Boxes
	MysteryBox *mysteryTmp;
	float mysteryBoxes[2][2] = {{146,438},{820,438}};
	for(unsigned int i = 0; i < (sizeof(mysteryBoxes)/sizeof(mysteryBoxes[0])); i++){
		mysteryTmp = new MysteryBox(mysteryBoxes[i][0],mysteryBoxes[i][1],0,GROUND,false);
		gameScene->addObject(mysteryTmp);
	}
	//Pipes
	staticPipe *staticPipeTmp;
	float staticPipes[5][2] = {{296,462},{464,462},{614,462},{870,462},{1500,462}};
	for(unsigned int i = 0; i < (sizeof(staticPipes)/sizeof(staticPipes[0])); i++){
		staticPipeTmp = new staticPipe(staticPipes[i][0],staticPipes[i][1],0,GROUND,false);
		gameScene->addObject(staticPipeTmp);
	}

	//Gombas
	gomba *gombaTmp;
	float gombas[9][2] = {{150,460},
						{320,460},{370,460},
						{500,460},
						{900,462},{1100,462},{1200,462},{1300,462},{1400,462}
						};
	for(unsigned int i = 0; i < (sizeof(gombas)/sizeof(gombas[0]));i++){
		gombaTmp = new gomba(gombas[i][0],gombas[i][1],0,ENEMY,true);
		gameScene->addObject(gombaTmp);
	}
	//koopas
	koopa *koopaTmp;
	float koopas[2][2] = {{560,460},{1000,460}};
	for(unsigned int i = 0; i < (sizeof(koopas)/sizeof(koopas[0]));i++){
		koopaTmp = new koopa(koopas[i][0],koopas[i][1],0,ENEMY,true);
		gameScene->addObject(koopaTmp);
	}


	//Edit views
	gameScene->getView(0)->setFollowing(p1,300,600);
	
	return gameScene;

}

Scene *createMenuScene(){

	Scene *menuScene = new Scene(600,520);

	//Create Objects
	background *bg = new background(0,0);

	//Ground
	ground *ground_object = new ground(0,342,0,GROUND,false);

	//Menu Text
	genericText *titleText = new genericText(0,0,-1,0,false);
	titleText->setText(100,150,24,false,"resources/arial.ttf","Super Zelski Bros");

	//Start Prompt
	genericText *promptText = new genericText(0,0,-1,0,false);
	promptText->setText(150,300,18,false,"resources/arial.ttf","Press X to Start");

	//gameTrigger
	gameTrigger *trigger = new gameTrigger(0,0,-1,0,false);

	//Add objects to the scenes
	menuScene->addObject(bg);
	menuScene->addObject(ground_object);
	menuScene->addObject(titleText);
	menuScene->addObject(promptText);
	menuScene->addObject(trigger);

	//Reset global variables
	currentLevel = 0;
	
	return menuScene;

}

Scene *createPreviewScene(){
	Scene *previewScene = new Scene(600,520);
	
	if(currentLevel < levels.size()){
		//Create Objects
		genericText *turnText = new genericText(0,0,-1,0,false);
		std::string turnString;

		genericText *lifeText = new genericText(0,0,-1,0,false);
		std::string lifeString;
		turnString = players[activePlayer].name; 
		turnString += "s Turn";
		lifeString = players[activePlayer].name;
		lifeString += " has " + std::to_string(players[activePlayer].lives) + " lives left";
		turnText->setText(150,50,18,false,"resources/arial.ttf",turnString);
		lifeText->setText(100,150,18,false,"resources/arial.ttf",lifeString);

		//timeTrigger
		timeTrigger *switchTrigger = new timeTrigger(0,0,-1,0,false);
		switchTrigger->setTimer(500.0);
		switchTrigger->setSceneFunc(levelFunc);
		switchTrigger->setSceneID(1);

		//Add objects to the scenes
		previewScene->addObject(lifeText);
		previewScene->addObject(turnText);
		previewScene->addObject(switchTrigger);
	}else{
		//Create Objects
		genericText *winString = new genericText(0,0,-1,0,false);
		winString->setText(150,50,18,false,"resources/arial.ttf","The Zelski Bros Win");

		//timeTrigger
		timeTrigger *switchTrigger = new timeTrigger(0,0,-1,0,false);
		switchTrigger->setTimer(1000.0);
		switchTrigger->setSceneFunc(createMenuScene);
		switchTrigger->setSceneID(0);

		//Add ojbects to the scene
		previewScene->addObject(winString);
		previewScene->addObject(switchTrigger);
	}


	return previewScene;

}



Scene *gameoverScene(){
	Scene *gameoverScene = new Scene(600,520);

	//Create Objects
	genericText *gameoverText = new genericText(0,0,-1,0,false);
	
	timeTrigger *switchTrigger = new timeTrigger(0,0,-1,0,false);
	switchTrigger->setTimer(700.0);
	switchTrigger->setSceneFunc(createMenuScene);
	switchTrigger->setSceneID(0);

	//Set text
	gameoverText->setText(150,50,24,false,"resources/arial.ttf","Game Over");

	//Add objects to the scene
	gameoverScene->addObject(gameoverText);
	gameoverScene->addObject(switchTrigger);
	

	return gameoverScene;
}
