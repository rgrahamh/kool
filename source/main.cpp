#include <iostream>
#include "headers/GameEngine.hpp"

using namespace std;

int main(){

	cout << "Hello World!" << endl;
	GameEngine myEngine = *(new GameEngine());
	Scene *firstScene = new Scene();
	Object *firstObject = new Object(50,50);
	firstScene->addObject(firstObject);

	myEngine.addScene(firstScene);


	myEngine.startGame();


	return 0;
}
