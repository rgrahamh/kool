#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "View.hpp"

class Scene{
	private:
			std::vector<View *> viewList;
			std::vector<Object *> objectList;
	public:
			Scene();
			void process();
			void render(sf::RenderWindow *window); //render(SFML window)
			int addObject(Object *object);
			int addView(View *view);

};
#endif
