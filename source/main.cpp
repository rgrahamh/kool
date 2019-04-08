#include <iostream>
#include "headers/GameEngine.hpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine(800,600,"Kool Engine"));

	//Create Scene
	Scene *firstScene = new Scene();

	//Create Object
	Object *firstObject = new Object(50,50);
	Object *secondObject = new Object(300,300);

	//Create Sprite
	Sprite *firstSprite = new Sprite("resources/pirate.png");
	Sprite *secondSprite = new Sprite("resources/dolphin.png");

	//Assign Sprite to Object
	firstObject->setSprite(firstSprite);
	secondObject->setSprite(secondSprite);

	//Assign Object to Scene
	firstScene->addObject(firstObject);
	firstScene->addObject(secondObject);

	//Assign Scene to Engine
	myEngine.addScene(firstScene);


	myEngine.startGame();


	return 0;
}
