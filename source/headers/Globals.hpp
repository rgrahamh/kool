#ifndef GLOBALS_H
#define GLOBALS_H
#include "GameEngine.hpp"
#include <vector>

extern std::vector<Sprite *> spriteIndex;
extern GameEngine *activeEngine;

extern void basicMove(float *x, float *y, int speed, double delta);

extern void createObject(Object *obj);

#endif
