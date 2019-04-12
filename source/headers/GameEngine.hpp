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
            int sceneID;
	public:
			GameEngine(int width,int height,std::string title);
			void startGame();
			void endGame();
			void addObject(Object *obj);
			int addScene(Scene *scene);
			bool delScene(int sceneID);
			bool setActiveScene(int sceneID);
			int nextScene();
			int prevScene();

};

#endif
