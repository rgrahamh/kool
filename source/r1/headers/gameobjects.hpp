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
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
    private:
        std::vector<Sprite*> sprites;
        bool grounded;
        float speed;
        float maxVelocity;
};

class Ground: public Object{
    public:
        Ground(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void create();
};

#endif
