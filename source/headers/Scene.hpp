#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <time.h>
#include "Object.hpp"
#include "View.hpp"

class Scene{
	private:
			double delta;
            clock_t lastFrame, thisFrame;

			std::vector<View *> viewList;
			std::vector<Object *> objectList;
	public:
			Scene();
			void process(); //Should make call to Object _process functions and to View _process functions
			void render(sf::RenderWindow *window); //render(SFML window)
			int addObject(Object *object);
			int addView(View *view);

};
#endif
