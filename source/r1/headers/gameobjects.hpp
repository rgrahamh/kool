#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include "../../headers/Object.hpp"
#include "../../headers/Globals.hpp"
#include <vector>

class Background: public Object{
    public:
		Background(float x, float y, unsigned int spriteIdx, int collisionLayer = -1, unsigned int collisionFlags = 0, bool grav = false);
        void create(unsigned int idx);
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
        bool oldGrounded;
        float speed;
        float maxVelocity;
        float shotTimer;
        int dir;
        bool jumpHeld;
        bool digitalJump;
        bool justJumped;
        bool digitalShoot;
        int health;
};

class Ground: public Object{
    public:
        Ground(float x, float y, int spriteIdx, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void create(int spriteIdx);
};

class Bullet: public Object{
    public:
        Bullet(float x, float y, float xSpeed, float ySpeed, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void onCollide(Object *other, int myBoxID, int otherBoxID);
        void create(float xSpeed, float ySpeed);
        int getDamage();
    private:
        int damage;
};

#endif
