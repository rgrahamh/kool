#ifndef VIEW_H
#define VIEW_H
#include "Object.hpp"

struct position{
	int x;
	int y;
};

class View{
	public:
		int windowX;
		int windowY;
		int width;
		int height;
		int sceneX;
		int sceneY;
		int followWidth;
		int followHeight;
		int followX;
		int followY;
		Object *following;
		

		View(int windowX,int windowY,int sceneX, int sceneY, int width, int height);
		/*
			Translate the supplied Scene coordinates into the window coordinates they correspond to
			based on this view. 
		*/
		struct position translate(int x, int y); 
		void _process();
		void follow(); //Adjust position based on the object we are following.


};
#endif
