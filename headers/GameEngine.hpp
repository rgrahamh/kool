class GameEngine {
	private:
			std::vector<Scene *> sceneList;
			void processScene();
			void renderScene();
	public:
			GameEngine();
			void startGame();
			void endGame();
			int addScene(Scene *scene);
			int delScene(Scene *scene);
			int setActiveScene(Scene *scene);
			int nextScene();
			int prevScene();

};
