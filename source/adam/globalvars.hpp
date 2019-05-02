#include "../headers/Scene.hpp"
#include "../headers/Globals.hpp"
#include <functional>
#include <string>
#include <SFML/Graphics.hpp>
extern int p1Lives;
extern int p2Lives;
extern int activePlayer;
extern int currentLevel;
extern std::function<Scene *()> levelFunc;
//Set organization:
//Right standing, left standing, right running, left running, right jumping, left jumping, dead
extern std::vector<unsigned int> p1Small;

//Super power enum
enum superPowers {
	FIREBOLT = 0x0,
	SUPERSPEED = 0x1,
	DASH = 0x2,
	TELEKINESIS = 0x4
};

//Player struct
struct playerData {
	int lives;
	bool isPlaying;
	std::string name;
	sf::Color pColor;
	superPowers powers;
};

extern struct playerData gracin;
extern struct playerData owen;
extern struct playerData madision;

extern struct playerData players[3];
extern int playerNum;
