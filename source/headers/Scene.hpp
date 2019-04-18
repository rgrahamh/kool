#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <time.h>
#include "Object.hpp"
#include "View.hpp"
#include "HitBox.hpp"

class Scene{
	private:
			double delta;
            clock_t lastFrame, thisFrame;

			std::vector<View *> viewList;
			std::vector<Object *> objectList;
	public:
			int width;
			int height;
			int id; //Where in the GameEngine list does this scene appear
			Scene(int width, int height);
			void process(); //Should make call to Object _process functions and to View _process functions
			void render(sf::RenderWindow *window); //render(SFML window)
			View *getView(unsigned int index);
			int addObject(Object *object);
			int addView(View *view);
			void setID(int id);
			std::vector<Object *> getObjectList();
			void destroyObject(Object *obj);

};
#endif
