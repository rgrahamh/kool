#ifndef OBJECT_H
#define OBJECT_H
#include <vector>
#include "HitBox.hpp"
#include "Sprite.hpp"

#define Keys sf::Keyboard

struct drawData {
	int x;
	int y;
	unsigned int imageIndex;
	Sprite *sprite;
	bool drawHitBoxes;
	int width;
	int height;
	bool repeated;
};

class Object{
	protected:

			int createHitBox(int offsetX,int offsetY,int width,int height,float ttl);

			/*
				Call HitBox.decTime and destroy hit box if ttl=0
			*/
			void decHitBoxes(double delta); 
			void addHitBox(int offsetX, int offsetY, int width, int height, double ttl=-1);
	public:
			float x;
			float y;

			/*
				When collisionLayer is 0, collide with everything. When collisionLayer is negative, doesn't collide with anything. Nonzero positive collisionLayer only collide with that layer
				Negative takes priority over zero. Meaning that should an object with cL = 0 collide with one with cL = -1, no collision processing should occur.
			*/
			int collisionLayer;
			
			/*
				Defined here instead of in Sprite object b/c same Sprite may be used for multiple object instances and will be at different points in animation
			*/
			unsigned int imageIndex; 
			bool dynamic;
			
			int renderLayer;

			/*
				Typically will be the same as in the Sprite instance, but it may be desired to be different for different objects so it is specified here as well.
			*/
			double animationSpeed; //Measured in milliseconds per image
			Sprite *sprite;
			std::vector<HitBox *> hitBoxes;


			Object(float x, float y);
            Object(float x, float y, Sprite *sprite, bool hasInitialHitbox);
			~Object();
			
			/*
				Call decHitBoxes() if X milliseconds have passed since last call.
			*/
			void _process(double delta); 
			void _destroy();

			//Debug toggle to do things like draw hitboxes
			bool debug;

			/*
				Calculate what imageIndex should be displayed, package all necessary rendering information into a drawData struct
			*/
			struct drawData _draw();

			virtual void process(double delta);
			virtual void onCollide(Object *other,int myBoxID, int otherBoxID);
			virtual void create();
			void setSprite(Sprite *sprite);
			void setSprite(unsigned int index);
			
			std::vector<HitBox *> getHitBoxes();

            //This line was erroring out if I didn't put it at the end of the definitions
			int collideWith[];
};
#endif
