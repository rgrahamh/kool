struct drawData {
	int x;
	int y;
	int imageIndex;
	Sprite *sprite;

};

class Object{
	private:
			float delta;
			
			int createHitBox(int offsetX,int offsetY,int width,int height,float ttl);

			/*
				Call HitBox.decTime and destroy hit box if ttl=0
			*/
			void decHitBoxes(float delta); 
	public:
			int x;
			int y;
			
			/*
				Defined here instead of in Sprite object b/c same Sprite may be used for multiple object instances and will be at different points in animation
			*/
			int imageIndex; 
			
			/*
				Typically will be the same as in the Sprite instance, but it may be desired to be different for different objects so it is specified here as well.
			*/
			int animationSpeed; 
			Sprite *sprite;
			std::vector<*HitBox> hitBoxes;

			Object(int x, int y);
			
			/*
				Call decHitBoxes() if X milliseconds have passed since last call.
			*/
			void _process(); 
			void _destroy();

			/*
				Calculate what imageIndex should be displayed, package all necessary rendering information into a drawData struct
			*/
			struct drawData _draw();

			virtual void process();
			virtual void onCollide(Object *other,int myBoxID, int otherBoxID);
			virtual void create();
			
			std::vector<*HitBox> getHitBoxes();

};
