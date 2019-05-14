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

class Background: public Object{
    public:
		Background(float x, float y, unsigned int spriteIdx, int collisionLayer = -1, unsigned int collisionFlags = 0, bool grav = false);
        void create(unsigned int idx);
};

class Character: public Object{
    public:
        Character(float x, float y, int maxHealth, unsigned char dir = 0, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        ~Character();
        void create(int maxHealth, unsigned char dir);
        virtual void process(double delta);
        virtual void onCollide(Object* other, int myBoxID, int theirBoxID);
        virtual void create();
    protected:
        std::vector<Sprite*> sprites;
        float speed;
        float maxVelocity;
        unsigned char dir;
        int health;
};

class Player: public Character{
    public:
		Player(float x, float y, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = true);
        ~Player();
        void create();
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
    private:
        bool grounded;
        bool oldGrounded;
        float shotTimer;
        float invinsTimer;
        bool jumpHeld;
        bool digitalJump;
        bool justJumped;
        bool digitalShoot;
        bool hurt;
};

class Joe: public Character{
    public:
		Joe(float x, float y, Character* following, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = true);
        ~Joe();
        void create(Character* following);
		void onCollide(Object *other, int myBoxID, int otherBoxID);
		void process(double delta);
    private:
        bool shielding;
        float stateTimer;
        float shotTimer;
        int shotsFired;
        Character* following;
};

class Ground: public Object{
    public:
        Ground(float x, float y, int spriteIdx, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
        void create(int spriteIdx);
};

class Bullet: public Object{
    public:
        Bullet(float x, float y, float xSpeed, float ySpeed, int damage, int collisionLayer = 0, unsigned int collisionFlags = 0, bool grav = false);
		void onCollide(Object *other, int myBoxID, int otherBoxID);
        void create(float xSpeed, float ySpeed, int damage);
        void process(double delta);
        int getDamage();
        void changeDirection(float xSpeed, float ySpeed);
    private:
        int damage;
};

#endif
