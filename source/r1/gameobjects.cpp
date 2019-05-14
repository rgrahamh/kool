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
    create(spriteIdx);
}

void Background::create(unsigned int idx){
    setSprite((unsigned int) idx);
}

//Character object
Character::Character(float x, float y, int maxHealth, unsigned char dir, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create(maxHealth, dir);
}

void Character::create(int maxHealth, unsigned char dir){
    this->health = maxHealth;
    this->dir = dir;
}

//These three stub functions are to prevent undefined references in the vtable
void Character::process(double delta){
    return;
}

void Character::onCollide(Object *other, int myBoxID, int otherBoxID){
	return;
}

void Character::create(){
	return;
}

Character::~Character(){}

//Player object
Player::Player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Character(x, y, 20, 1, collisionLayer, collisionFlags, grav){
    create();
}

void Player::create(){
    this->collisionLayer = 0;
    this->collisionFlags = PLAYER;
    this->debug = false;
    this->invinsTimer = 0;

    this->animationDelay = 25;

    //Adding all of the Mega Man sprites to a list

    /** SPRITE INDICIES:
     * 0: Standing left        
     * 1: Standing right       
     * 2: Standing shooting left        
     * 3: Standing shooting right       
     * 4: Running left         
     * 5: Running right        
     * 6: Shooting running left
     * 7: Shooting running right
     * 8: Jumping left
     * 9: Jumping right
     * 10: Jumping shooting left
     * 11: Jumping shooting right
     * 12: Hurt left
     * 13: Hurt right
     */
    sprites.push_back(this->getSprite(1)); 
    sprites.push_back(this->getSprite(2)); 
    sprites.push_back(this->getSprite(3)); 
    sprites.push_back(this->getSprite(4)); 
    sprites.push_back(this->getSprite(5)); 
    sprites.push_back(this->getSprite(6)); 
    sprites.push_back(this->getSprite(7)); 
    sprites.push_back(this->getSprite(8)); 
    sprites.push_back(this->getSprite(9)); 
    sprites.push_back(this->getSprite(10));
    sprites.push_back(this->getSprite(11)); 
    sprites.push_back(this->getSprite(12));
    sprites.push_back(this->getSprite(13)); 
    sprites.push_back(this->getSprite(14));
    sprites.push_back(this->getSprite(25));
    this->setSprite(sprites[0]);

	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.35;
    this->speed = 2.5;
	this->maxVelocity = 5.0;
    this->collisionLayer = 0;

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
        if(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY && !(oldThisX + this->hitBoxes[myBoxID]->width <= oldOtherX || thisX <= otherX + other->hitBoxes[otherBoxID]->width && oldThisX >= oldOtherX + other->hitBoxes[otherBoxID]->width)){
                this->y = otherY - this->hitBoxes[myBoxID]->height;
                this->yV = 0;
                //Necessary to check grounded a frame prior because collision detection happens after the process step
                if(oldGrounded == false){
                    playSound((char*)"./resources/r1/sound/land.wav");
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
    }

    if((other->collisionFlags & ENEMY) && invinsTimer < 0){
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
    int spriteIdx;

    oldGrounded = grounded;

    //Jumping
    if(Keys::isKeyPressed(Keys::W) && grounded && !digitalJump && invinsTimer < 400){
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
    if((Keys::isKeyPressed(Keys::A) || Keys::isKeyPressed(Keys::D)) && invinsTimer < 400){
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

    //Flickering on invinsibility
    if(invinsTimer >= 0 && ((int)invinsTimer) % 100 > 50){
        spriteIdx = 25;
    }
    
    //Update sprite with current state
    this->setSprite(spriteIdx);

    sf::Texture currImage = sprite->getImage(this->imageIndex);
    this->sprite->setSize(currImage.getSize().x, currImage.getSize().y);

    //Shooting
    if(Keys::isKeyPressed(Keys::Space) && !digitalShoot && invinsTimer < 400){
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

    grounded = false;
    
    //Checking for death
    if(!inView(this, activeEngine->getActiveScene()->id, 0) || health <= 0){
        resetScene(createMainGame(), activeEngine->getActiveScene()->id)
    }
    
}

Player::~Player(){}

Joe::Joe(float x, float y, Character* following, int collisionLayer, unsigned int collisionFlags, bool grav):Character(x, y, 20, 0, collisionLayer, collisionFlags, grav){
    create(following);
}

void Joe::create(Character* following){
    this->following = following;
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

Joe::~Joe(){}

Ground::Ground(float x, float y, int spriteIdx, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create(spriteIdx);
}

void Ground::create(int spriteIdx){
    this->collisionLayer = 0;
    this->debug=false;
    this->collisionFlags = GROUND;

    setSprite((unsigned int)spriteIdx);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}

Bullet::Bullet(float x, float y, float xSpeed, float ySpeed, int damage, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags | PROJECTILE, grav){
    create(xSpeed, ySpeed, damage);
}

void Bullet::onCollide(Object *other, int myBoxID, int otherBoxID){
    if(other->collisionFlags & GROUND){
        destroyObject(this);
    }
}

void Bullet::create(float xSpeed, float ySpeed, int damage){
    this->debug = false;
    this->friction = 0;
    this->xV = xSpeed;
    this->yV = ySpeed;
    this->damage = damage;
    
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
