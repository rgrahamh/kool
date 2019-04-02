class Scene{
	private:
			std::vector<View *> viewList;
			std::vector<Object *> objectList;
			std::vector<Sprite *> spriteList;
	public:
			Scene();
			void process();
			void render();
			int addObject(Object *object);
			int addView(View *view);
			int addSprite(Sprite *sprite);

};
