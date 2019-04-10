#ifndef GLOBALS_H
#define GLOBALS_H
#include "Sprite.hpp"
#include <vector>

extern std::vector<Sprite *> spriteIndex;

extern void basicMove(float *x, float *y, int speed, double delta);

#endif
