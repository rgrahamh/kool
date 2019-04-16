#include <iostream>
#include "headers/GameEngine.hpp"
#include "testObj.cpp"
#include "testObj2.cpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine(1080,720,"Kool Engine"));

	//Create Scene
	Scene *firstScene = new Scene(1000,700);

	Scene *secondScene = new Scene(1000,700);

	//Create Sprite
	Sprite *firstSprite = new Sprite("resources/bill.png");
	Sprite *bg = new Sprite("resources/background.png");

	//Create Objects
	testObj *firstObject = new testObj(50.0,50.0);

	testObj *secondObject = new testObj(500,500);
	testObj *thirdObject = new testObj(400,500);
	testObj *fourthObject = new testObj(300,500);
	testObj *fifthObject = new testObj(200,500);

    testObj2 *sixthObject = new testObj2(500, 80);

	Object *background = new Object(0,0);
	Object *background2 = new Object(1080,0);
	Object *background3 = new Object(0,720);
	background->setSprite(bg);
	background2->setSprite(bg);
	background3->setSprite(bg);

	//Assign Object to Scene
	firstScene->addObject(background);
	firstScene->addObject(background2);
	firstScene->addObject(background3);
	firstScene->addObject(firstObject);
	firstScene->addObject(firstObject);
	firstScene->addObject(thirdObject);
	firstScene->addObject(fourthObject);
	firstScene->addObject(fifthObject);
    firstScene->addObject(sixthObject);

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
