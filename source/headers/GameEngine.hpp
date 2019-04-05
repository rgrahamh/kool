#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

class GameEngine {
	private:
			std::vector<Scene *> sceneList;
			Scene *activeScene;
			void processScene();
			void renderScene();
			//SFML Window object kept here.
			sf::RenderWindow *window;
			sf::Event event;
	public:
			GameEngine();
			void startGame();
			void endGame();
			int addScene(Scene *scene);
			int delScene(Scene *scene);
			int setActiveScene(Scene *scene);
			int nextScene();
			int prevScene();

};

#endif
