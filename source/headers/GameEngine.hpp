#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"
#include "View.hpp"

class GameEngine {
	private:
			std::vector<Scene *> sceneList;
			Scene *activeScene;
			void processScene();
			void renderScene();
			//SFML Window object kept here.
			sf::RenderWindow *window;
			sf::Event event;
			int winWidth;
			int winHeight;
	public:
			GameEngine(int width,int height,std::string title);
			void startGame();
			void endGame();
			int addScene(Scene *scene);
			int delScene(Scene *scene);
			int setActiveScene(Scene *scene);
			int nextScene();
			int prevScene();

};

#endif
