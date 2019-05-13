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
extern bool activeDead;


