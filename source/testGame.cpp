#include <iostream>
#include "headers/GameEngine.hpp"
#include "testObj.cpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine(1080,720,"Kool Engine"));

	//Create Scene
	Scene *firstScene = new Scene(1080,700);

	Scene *secondScene = new Scene(1080,700);

	//Create Sprite
<<<<<<< HEAD
	Sprite *firstSprite = new Sprite("resources/bill.png");
=======
	Sprite *firstSprite = new Sprite("resources/bill.png");
//	firstSprite->setRepeated(true);
//	firstSprite->setSize(32,16);
	Sprite *ground = new Sprite("resources/ground.png");
	ground->setRepeated(true);
	ground->setSize(2000,32);

>>>>>>> a483739e02893f5ffcad8ba53b80a229faa7cd85
	Sprite *bg = new Sprite("resources/background.png");

	//Create Objects
	testObj *firstObject = new testObj(50,50);

	testObj *secondObject = new testObj(500,500);
	testObj *thirdObject = new testObj(400,500);
	testObj *fourthObject = new testObj(300,500);
	testObj *fifthObject = new testObj(200,500);

	Object *background = new Object(0,0);
	Object *background2 = new Object(1080,0);
	Object *background3 = new Object(0,720);
	Object *floor = new Object(0.0,700.0,ground,true);
//	Object *floor = new Object(0.0,700.0);
	background->setSprite(bg);
	background2->setSprite(bg);
	background3->setSprite(bg);
//	floor->setSprite(ground);

	//Assign Object to Scene
	firstScene->addObject(background);
	firstScene->addObject(background2);
	firstScene->addObject(background3);
	firstScene->addObject(floor);
	firstScene->addObject(firstObject);

	secondScene->addObject(background);
	secondScene->addObject(secondObject);
	secondScene->addObject(thirdObject);
	secondScene->addObject(fourthObject);
	secondScene->addObject(fifthObject);

	firstObject->xSwitch = 0;
//	firstScene->addObject(secondObject);
//	firstScene->addObject(thirdObject);
//	firstScene->addObject(base);

	//Assign Scene to Engine
	myEngine.addScene(firstScene);
	myEngine.addScene(secondScene);

	//Edit Views
	firstScene->getView(0)->setFollowing(firstObject,400,400);


	myEngine.startGame();


	return 0;
}
