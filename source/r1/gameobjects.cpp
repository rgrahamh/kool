#include "./headers/gameobjects.hpp"

#define SCALE 2.0

using namespace std;

//Title object
Title::Title(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Title::create(){
    setSprite((unsigned int)26);
}

void Title::process(double delta){
    if(Keys::isKeyPressed(Keys::Space)){
        setActiveScene(1);
    }
}

//Background object
Background::Background(float x, float y, unsigned int spriteIdx, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    this->spriteIdx = spriteIdx;
    create();
}

void Background::create(){
    setSprite((unsigned int)spriteIdx);
}

//Character object
Character::Character(float x, float y, int maxHealth, unsigned char dir, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    this->health = maxHealth;
    this->dir = dir;
}

//Player object
Player::Player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Character(x, y, 5, 1, collisionLayer, collisionFlags, grav){
    create();
}

void Player::create(){
    this->collisionLayer = 0;
    this->collisionFlags = PLAYER;
    this->debug = false;
    this->invinsTimer = 0;
    this->dead = false;
    this->deathTimer = 0;

    this->animationDelay = 25;

    this->setSprite((unsigned int)1);

	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.35;
    this->speed = 2.5;
	this->maxVelocity = 5.0;
    this->collisionLayer = 0;

    this->warp = true;
    this->won = false;

    this->dir = 1;

    grounded = false;
}

void Player::onCollide(Object *other, int myBoxID, int otherBoxID){
    //If the player collides with ground:
    if(other->collisionFlags & GROUND){
        int thisX = this->x + this->hitBoxes[myBoxID]->offsetX;
        int thisY = this->y + this->hitBoxes[myBoxID]->offsetY;

        int oldThisX = this->xPrev + this->hitBoxes[myBoxID]->offsetX;
        int oldThisY = this->yPrev + this->hitBoxes[myBoxID]->offsetY;

        int otherX = other->x + other->hitBoxes[otherBoxID]->offsetX;
        int otherY = other->y + other->hitBoxes[otherBoxID]->offsetY;

        int oldOtherX = other->xPrev + this->hitBoxes[otherBoxID]->offsetX;
        int oldOtherY = other->yPrev + this->hitBoxes[otherBoxID]->offsetY;


        //Bottom of this colllides with top of other
        if(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY && !((thisX + this->hitBoxes[myBoxID]->width >= otherX && oldThisX + this->hitBoxes[myBoxID]->width <= oldOtherX) || (thisX <= otherX + other->hitBoxes[otherBoxID]->width && oldThisX >= oldOtherX + other->hitBoxes[otherBoxID]->width))){
                this->y = otherY - this->hitBoxes[myBoxID]->height;
                this->yV = 0;
                //Necessary to check grounded a frame prior because collision detection happens after the process step
                if(oldGrounded == false){
                    playSound((char*)"./resources/r1/sound/land.wav");
                }
                if(!won){
                    if(warp){
                        playSound((char*)"./resources/r1/sound/beam-down.wav");
                        this->warp = false;
                        this->gravity = true;
                    }
                }
                grounded = true;
        }
        //Top of this collides with bottom of other
        else if(thisY < otherY + other->hitBoxes[otherBoxID]->height && oldThisY >= oldOtherY + other->hitBoxes[otherBoxID]->height){
            this->y = otherY + other->hitBoxes[otherBoxID]->height;
            this->yV = 0;
        }
        //Right side of this collides with left side of other
        else if(thisX + this->hitBoxes[myBoxID]->width >= otherX && oldThisX + this->hitBoxes[myBoxID]->width <= oldOtherX && !(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY)){ 
            this->x = otherX - this->hitBoxes[myBoxID]->width;
            this->xV = 0;
        }
        //Left side of this collides with right side of other
        else if(thisX <= otherX + other->hitBoxes[otherBoxID]->width && oldThisX >= oldOtherX + other->hitBoxes[otherBoxID]->width && !(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY)){ 
            this->x = otherX + other->hitBoxes[otherBoxID]->width;
            this->xV = 0;
        }
        //Otherwise, send them back from whence they came.
        else if((oldThisX > oldOtherX && oldThisX > oldOtherX + other->hitBoxes[otherBoxID]->width && oldThisY > oldOtherY && oldThisY > oldOtherY + other->hitBoxes[otherBoxID]->height) || (oldOtherX > oldThisX && oldOtherX > oldThisX + this->hitBoxes[myBoxID]->width && oldOtherY > oldThisY && oldOtherY > oldThisY + this->hitBoxes[myBoxID]->width)){
            this->x = this->xPrev;
        }
    }

    if(other->collisionFlags & PICKUP){
        won = true;
        warp = true;
        playSound((char*)"./resources/r1/sound/beam-up.wav");
        destroyObject(other);
        return;
    }

    if((other->collisionFlags & ENEMY) && invinsTimer <= 0){
        invinsTimer = 500;
        xV += 40.0 * ((dir)? -1 : 1);
        playSound((char*)"./resources/r1/sound/hurt.wav");
        if(other->collisionFlags & PROJECTILE){
            this->health -= ((Bullet*)other)->getDamage();
            destroyObject(other);
        }
        else{
            this->health -= 1;
        }
    }
}

void Player::process(double delta){
    if(warp){
        gravity = false;
        yV = 0;
        y += 20.0 * ((won)? -1 : 1);
        setSprite(30);

        if(!inView(this, activeEngine->getActiveScene()->id, 0)  && won){
            setActiveScene(0);
            resetScene(createMainGame, 1);
        }
    }else{
        int spriteIdx;

        oldGrounded = grounded;

        //Jumping
        if(Keys::isKeyPressed(Keys::W) && grounded && !digitalJump && invinsTimer < 400 && !dead){
            yA -= 20.0;
            digitalJump = true;
            jumpHeld = true;
        } else {
            if(!Keys::isKeyPressed(Keys::W) && jumpHeld){
                jumpHeld = false;
                if(yV < 0){
                    yV = 0;
                }
            }
            if(!Keys::isKeyPressed(Keys::W) && grounded){
                digitalJump = false;
            }
        }

        //Moving left and right
        if((Keys::isKeyPressed(Keys::A) || Keys::isKeyPressed(Keys::D)) && invinsTimer < 400 && !dead){
            spriteIdx = 0;
            if(!(Keys::isKeyPressed(Keys::A) && Keys::isKeyPressed(Keys::D))){ //If both are pressed, do nothing.
                if(Keys::isKeyPressed(Keys::A)){
                    xA -= speed;
                    this->dir = 0;
                }
                if(Keys::isKeyPressed(Keys::D)){
                    xA += speed;
                    this->dir = 1;
                }
                spriteIdx = 5 + dir;
            }
            else{
                spriteIdx = 1 + dir;
            }
        } else {
            spriteIdx = 1 + dir;
        }

        if(!grounded){
            spriteIdx = 9 + dir;
        }
        if(shotTimer > 0){
            spriteIdx += 2;
        }

        if(invinsTimer > 400){
            spriteIdx = 13 + dir;
        }

        //Flickering on invinsibility (or invisible on death)
        if((invinsTimer >= 0 && ((int)invinsTimer) % 50 > 25) || dead){
            spriteIdx = 25;
        }
        
        //Update sprite with current state
        this->setSprite(spriteIdx);

        sf::Texture currImage = sprite->getImage(this->imageIndex);
        this->sprite->setSize(currImage.getSize().x, currImage.getSize().y);

        //Shooting
        if(Keys::isKeyPressed(Keys::Space) && !digitalShoot && invinsTimer < 400 && !dead){
            Bullet* shot = new Bullet(this->x + ((dir)? currImage.getSize().x : 0), this->y + (currImage.getSize().y / 2), 20.0 * ((dir)? 1 : -1), 0.0, 1, 0, PLAYER, false);

            //Scale the bullet
            shot->setScale(SCALE, SCALE);
            shot->hitBoxes[0]->height *= SCALE;
            shot->hitBoxes[0]->width *= SCALE;

            //Finish creating the bullet in the scene
            createObject(shot);
            shotTimer = 50;
            digitalShoot = true;

            playSound((char*)"./resources/r1/sound/shoot.wav");
        }
        else if(!Keys::isKeyPressed(Keys::Space)){
            digitalShoot = false;
        }
        
        //Making sure that the player doesn't escape the screen's left bound
        if(this->x + this->xV < 0){
            this->x = 0;
            this->xV = 0;
        }

        if(this->xV > this->maxVelocity){
            xV = maxVelocity;
        }
        else if(this->xV < this->maxVelocity * -1){
            xV = maxVelocity * -1;
        }

        if(shotTimer >= 0){
            shotTimer -= delta;
        }

        if(invinsTimer >= 0){
            invinsTimer -= delta;
        }

        if(deathTimer > 0){
            deathTimer -= delta;
        }

        grounded = false;
        
        //Checking for death
        if((!inView(this, activeEngine->getActiveScene()->id, 0) || health <= 0) && !dead && !won){
            playSound((char*)"./resources/r1/sound/death.wav");
            deathTimer = 500;
            dead = true;
        }

        if(dead && deathTimer <= 0){
            setActiveScene(0);
            resetScene(createMainGame, 1);
        }
    }
}

Joe::Joe(float x, float y, Character* following, int collisionLayer, unsigned int collisionFlags, bool grav):Character(x, y, 20, 0, collisionLayer, collisionFlags, grav){
    this->following = following;
    create();
}

void Joe::create(){
    this->shielding = false;
    this->stateTimer = 750;

    setSprite((unsigned int)21);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void Joe::process(double delta){
    if(inView(this, activeEngine->getActiveScene()->id, 0)){
        if(health <= 0){
            destroyObject(this);
            playSound((char*)"./resources/r1/sound/destroy.wav");
            return;
        }

        if(following->x < this->x){
            dir = 0;
        } else {
            dir = 1;
        }

        if(stateTimer <= 0){
            if(shielding){
                shielding = false;
                stateTimer = 1250;
                shotTimer = 200;
            } else {
                shielding = true;
                stateTimer = 1000;
            }
        }

        if(!shielding && shotTimer <= 0){
            playSound((char*)"./resources/r1/sound/enemy-shoot.wav");
            sf::Texture currImage = this->sprite->getImage(this->imageIndex);
            Bullet* shot = new Bullet(this->x + ((dir)? currImage.getSize().x : 0), this->y + (currImage.getSize().y / 2), 15.0 * ((dir)? 1 : -1), 0.0, 1, 0, ENEMY, false);

            //Scale the bullet
            shot->setScale(SCALE, SCALE);
            shot->hitBoxes[0]->height *= SCALE;
            shot->hitBoxes[0]->width *= SCALE;

            //Finish creating the bullet in the scene
            createObject(shot);
            shotTimer = 200;
        }
        int spriteIdx = 21;

        if(!shielding){
            spriteIdx += 2;
        }

        //Update sprite with current state
        this->setSprite(spriteIdx + dir);

        stateTimer -= delta;
        shotTimer -= delta;
    }
}

void Joe::onCollide(Object *other, int myBoxID, int otherBoxID){
    if(inView(this, activeEngine->getActiveScene()->id, 0)){
        if((other->collisionFlags & PLAYER) && (other->collisionFlags & PROJECTILE)){
            if(!shielding){
                playSound((char*)"./resources/r1/sound/enemy-hurt.wav");
                health -= ((Bullet*)other)->getDamage();
                destroyObject(other);
            } else {
                playSound((char*)"./resources/r1/sound/dink.wav");
                ((Bullet*)other)->changeDirection(other->xV * -1.0, other->xV * ((other->xV > 0)? -1 : 1));
            }
        }
    }
}

Chicken::Chicken(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Character(x, y, 25, 0, collisionLayer, collisionFlags, grav){
    create();
}

void Chicken::create(){
    this->dir = 1;
    this->xV = 15.0;
    this->animationTime = 20;

    setSprite(28);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void Chicken::process(double delta){
    setSprite(28 + dir);

    if(health <= 0){
        Pickup* pickup = new Pickup(this->x + (this->sprite->width / 2), this->y);

        pickup->setScale(SCALE, SCALE);
        pickup->hitBoxes[0]->height *= SCALE;
        pickup->hitBoxes[0]->width *= SCALE;

        createObject(pickup);

        destroyObject(this);
        playSound((char*)"./resources/r1/sound/destroy.wav");
        return;
    }
}

void Chicken::onCollide(Object *other, int myBoxID, int otherBoxID){
    if(other->collisionFlags & GROUND){
        dir = !dir;
        xV *= -1.0;
    }
    if((other->collisionFlags & PLAYER) && (other->collisionFlags & PROJECTILE)){
        playSound((char*)"./resources/r1/sound/enemy-hurt.wav");
        health -= ((Bullet*)other)->getDamage();
        destroyObject(other);
    }
}

Ground::Ground(float x, float y, int spriteIdx, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    this->spriteIdx = spriteIdx;
    create();
}

void Ground::create(){
    this->collisionLayer = 0;
    this->debug=false;
    this->collisionFlags = GROUND;

    setSprite((unsigned int)spriteIdx);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

Bullet::Bullet(float x, float y, float xSpeed, float ySpeed, int damage, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags | PROJECTILE, grav){
    this->xV = xSpeed;
    this->yV = ySpeed;
    this->damage = damage;
    create();
}

void Bullet::onCollide(Object *other, int myBoxID, int otherBoxID){
    if(other->collisionFlags & GROUND){
        destroyObject(this);
    }
}

void Bullet::create(){
    this->debug = false;
    this->friction = 0;
    
    setSprite((unsigned int)19);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void Bullet::process(double delta){
    if(!inView(this, activeEngine->getActiveScene()->id, 0)){
        destroyObject(this);
    }
}

int Bullet::getDamage(){
    return this->damage;
}

void Bullet::changeDirection(float xSpeed, float ySpeed){
    this->xV = xSpeed;
    this->yV = ySpeed;
}

Pickup::Pickup(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags | PICKUP, grav){
    create();
}

void Pickup::create(){
    setSprite((unsigned int)33);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

void Pickup::onCollide(Object* other, int myBoxID, int otherBoxID){
    int thisY = this->y + this->hitBoxes[myBoxID]->offsetY;
    int oldThisY = this->yPrev + this->hitBoxes[myBoxID]->offsetY;
    int otherY = other->y + other->hitBoxes[otherBoxID]->offsetY;
    int oldOtherY = other->yPrev + this->hitBoxes[otherBoxID]->offsetY;

    if(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY){
        this->y = otherY - this->hitBoxes[myBoxID]->height;
        this->yV = 0;
    }
}
