#ifndef GAME_OBJ_H
#define GAME_OBJ_H
#include "../../headers/Object.hpp"
#include "../../headers/Globals.hpp"
#include "./scenes.hpp"
#include <vector>

class Title: public Object{
    public:
		Title(float x, float y, int collisionLayer = -1, unsigned int collisionFlags = 0, bool grav = false);
        void create();
        void process(double delta);
};

class SceneProgressor : public Object{
    public:
        SceneProgressor(int nextScene, Keys::Key key, char* soundFile = NULL, bool looping = false);
        void process(double delta);
    private:
        Keys::Key key;
        int nextScene;
        char* soundFile;
        bool looping;
};

class Background: public Object{
    public:
		Background(float x, float y, unsigned int spriteIdx, int collisionLayer = -1, unsigned int collisionFlags = 0, bool grav = false);
        void create();
    private:
        int spriteIdx;
};

class Character: public Object{
    public:
        Character(float x, float y, int maxHealth, unsigned char dir = 0, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
    protected:
        float speed;
        float maxVelocity;
        unsigned char dir;
        int health;
};

class Player: public Character{
    public:
		Player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = PLAYER, bool grav = true);
        void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
    private:
        bool grounded;
        bool oldGrounded;
        float shotTimer;
        float invinsTimer;
        float deathTimer;
        bool dead;
        bool jumpHeld;
        bool digitalJump;
        bool justJumped;
        bool digitalShoot;
        bool hurt;
        bool warp;
        bool won;
};

class Joe: public Character{
    public:
		Joe(float x, float y, Character* following, int collisionLayer = 0, unsigned int collisionFlags = ENEMY, bool grav = false);
        void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
    private:
        Character* following;
        bool shielding;
        float stateTimer;
        float shotTimer;
        int shotsFired;
};

class Chicken: public Character{
    public:
        Chicken(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = ENEMY, bool grav = false);
        void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
        void process(double delta);
    private:
        float speed;
};

class Ground: public Object{
    public:
        Ground(float x, float y, int spriteIdx, int collisionLayer = 0, unsigned int collisionFlags = GROUND, bool grav = false);
        void create();
    private:
        int spriteIdx;
};

class Bullet: public Object{
    public:
        Bullet(float x, float y, float xSpeed, float ySpeed, int damage, int collisionLayer = 0, unsigned int collisionFlags = PROJECTILE, bool grav = false);
		void onCollide(Object *other, int myBoxID, int otherBoxID);
        void create();
        void process(double delta);
        int getDamage();
        void changeDirection(float xSpeed, float ySpeed);
    private:
        int damage;
};

class Pickup: public Object{
    public:
        Pickup(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = PICKUP, bool grav = true);
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void create();
};

#endif
