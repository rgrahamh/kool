#include <iostream>
#include "headers/GameEngine.hpp"
#include "testObj.cpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine(1080,720,"Kool Engine"));

	//Create Scene
	Scene *firstScene = new Scene();
	Scene *secondScene = new Scene();

	//Create Sprite
	Sprite *firstSprite = new Sprite("resources/bill.png");

	//Create Object
	testObj *firstObject = new testObj(50,50);

	testObj *secondObject = new testObj(500,500);
	testObj *thirdObject = new testObj(400,500);
	testObj *fourthObject = new testObj(300,500);
	testObj *fifthObject = new testObj(200,500);

	//Assign Object to Scene
	firstScene->addObject(firstObject);

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


	myEngine.startGame();


	return 0;
}
