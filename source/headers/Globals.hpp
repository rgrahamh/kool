#ifndef GLOBALS_H
#define GLOBALS_H
#include "GameEngine.hpp"
#include "../irrKlang-64bit-1.6.0/include/irrKlang.h"
#include <vector>

extern std::vector<Sprite *> spriteIndex;
extern GameEngine *activeEngine;
extern irrklang::ISoundEngine *soundEngine;

extern void basicMove(float *xA, float *yA, float speed, double delta);

extern void directMove(float *x, float *y, float speed, double delta);

extern void createObject(Object *obj);

extern void destroyObject(Object *obj);

extern bool setActiveScene(int sceneID);

extern void playSound(char *filename, irrklang::ISoundEngine *engine, bool loop);

extern void stopAllSounds(irrklang::ISoundEngine *engine);

extern int getSceneWidth(int sceneID);

extern int getSceneWidth();

extern int getSceneHeight(int sceneID);

extern int windowWidth;

extern int windowHeight;

extern int getWindowWidth();

extern int getWindowHeight();

extern int resetScene(Scene* (*buildFunction)(),int sceneID);

#endif
