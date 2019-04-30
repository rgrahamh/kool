#include "../headers/Scene.hpp"
#include <functional>
#include <string>
extern int p1Lives;
extern int p2Lives;
extern int activePlayer;
extern int currentLevel;
extern std::function<Scene *()> levelFunc;

//Player struct
struct playerData {
	int lives;
	bool isPlaying;
	std::string name;
};

extern struct playerData gracin;
extern struct playerData owen;
extern struct playerData madision;

extern struct playerData players[3];
extern int playerNum;
