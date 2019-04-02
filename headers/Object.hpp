struct drawData {
	int x;
	int y;
	int spriteIndex;
	int animationSpeed;
	Sprite *sprite;

};

class Object{
	private:
			float delta;
	public:
			int x;
			int y;
			int spriteIndex; //Defined here instead of in Sprite object b/c same Sprite may be used for multiple object instances and will be at different points in animation
			int animationSpeed; //Typically will be the same as in the Sprite instance, but it may be desired to be different for different objects so it is specified here as well.
			Sprite *sprite;

			Object();
			void _process();
			virtual void process(); 
			virtual struct drawData draw();
			virtual void onCollide(Object *other);

};
