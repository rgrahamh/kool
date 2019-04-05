#ifndef VIEW_H
#define VIEW_H

struct position{
	int x;
	int y;
}

class View{
	public:
		int windowX;
		int windowY;
		int width;
		int height;
		int sceneX;
		int sceneY;
		Object *following;
	
		/*
			Translate the supplied Scene coordinates into the window coordinates they correspond to
			based on this view. 
		*/
		struct position translate(int x, int y); 
		void _process();
		void follow(); //Adjust position based on the object we are following.


};
#endif
