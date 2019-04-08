#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Object.hpp"
#include "View.hpp"
#include "Input.hpp"

class Scene{
	private:
			std::vector<View *> viewList;
			std::vector<Object *> objectList;
			Input input;
	public:
			Scene();
			void process(); //Should make call to Object _process functions and to View _process functions
			void render(sf::RenderWindow *window); //render(SFML window)
			int addObject(Object *object);
			int addView(View *view);

};
#endif
