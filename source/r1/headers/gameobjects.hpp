#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include "../../headers/Object.hpp"
#include <vector>

class Background: public Object{
    public:
		Background(float x, float y, int collisionLayer = -1, unsigned int collisionFlags = 0, bool grav = false);
        void create();
};

class Player: public Object{
    public:
		Player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void create();
    private:
        std::vector<Sprite*> sprites;
};

class Ground: public Object{
    public:
        Ground(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void create();
};

#endif
