#include <iostream>
#include "headers/GameEngine.hpp"
#include "testObj.cpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine(1080,720,"Kool Engine"));

	//Create Scene
	Scene *firstScene = new Scene();

	//Create Object
	testObj *firstObject = new testObj(50,50);
	testObj *secondObject = new testObj(300,300);
	testObj *thirdObject = new testObj(700,400);

	//Create Sprite
	Sprite *firstSprite = new Sprite("resources/pirate.png");

	//Assign Sprite to Object
	firstObject->setSprite(firstSprite);
	secondObject->setSprite(firstSprite);
	thirdObject->setSprite(firstSprite);

	//Assign Object to Scene
	firstScene->addObject(firstObject);
	firstScene->addObject(secondObject);
	firstScene->addObject(thirdObject);

	//Assign Scene to Engine
	myEngine.addScene(firstScene);


	myEngine.startGame();


	return 0;
}
