#include "./headers/gameobjects.hpp"

#define SCALE 2.0

using namespace std;


//Background object
Background::Background(float x, float y, unsigned int spriteIdx, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create(spriteIdx);
}

void Background::create(unsigned int idx){
    setSprite((unsigned int) idx);
}

//Player object
Player::Player(float x, float y, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create();
}

void Player::create(){
    this->collisionLayer = 0;
    this->collisionFlags = PLAYER;
    this->debug = false;

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
    this->setSprite(sprites[0]);

	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
	this->friction = 0.35;
	this->speed = 1.2;
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

        //printf("thisX: %d\nthisY: %d\noldThisX: %d\noldThisY: %d\n\n", thisX, thisY, oldThisX, oldThisY);

        //Bottom of this colllides with top of other
        if(thisY + this->hitBoxes[myBoxID]->height >= otherY && oldThisY + this->hitBoxes[myBoxID]->height <= oldOtherY){
                this->y = otherY - this->hitBoxes[myBoxID]->height;
                this->yV = 0;
                //Necessary to check grounded a frame prior because collision detection happens after the process step
                if(oldGrounded == false){
                    playSound("./resources/r1/sound/land.wav");
                }
                grounded = true;
        }
        //Top of this collides with bottom of other
        else if(thisY < otherY + other->hitBoxes[otherBoxID]->height && oldThisY >= oldOtherY + other->hitBoxes[otherBoxID]->height){
            this->y = otherY + other->hitBoxes[otherBoxID]->height;
            this->yV = 0;
        }
        //Right side of this collides with left side of other
        else if(thisX + this->hitBoxes[myBoxID]->width >= otherX && oldThisX + this->hitBoxes[myBoxID]->width <= oldOtherX){ 
            this->x = otherX - this->hitBoxes[myBoxID]->width;
            this->xV = 0;
        }
        //Left side of this collides with right side of other
        else if(thisX <= otherX + other->hitBoxes[otherBoxID]->width && oldThisX >= oldOtherX + other->hitBoxes[otherBoxID]->width){ 
            this->x = otherX + other->hitBoxes[otherBoxID]->width;
            this->xV = 0;
        }
    }
}

void Player::process(double delta){
    int spriteIdx;

    oldGrounded = grounded;

    //Jumping
    if(Keys::isKeyPressed(Keys::W) && grounded && !digitalJump){
        printf("Jump!\n");
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
    if(Keys::isKeyPressed(Keys::A) || Keys::isKeyPressed(Keys::D)){
        spriteIdx = 0;
        if(!(Keys::isKeyPressed(Keys::A) && Keys::isKeyPressed(Keys::D))){ //If both are pressed, do nothing.
            if(Keys::isKeyPressed(Keys::A)){
                xA -= speed * delta;
                this->dir = 0;
            }
            if(Keys::isKeyPressed(Keys::D)){
                xA += speed * delta;
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
    
    //Update sprite with current state
    this->setSprite(spriteIdx);

    sf::Texture currImage = sprite->getImage(this->imageIndex);
    this->sprite->setSize(currImage.getSize().x, currImage.getSize().y);

    //Shooting
    if(Keys::isKeyPressed(Keys::Space) && !digitalShoot){
        Bullet* shot = new Bullet(this->x + ((dir)? currImage.getSize().x : 0), this->y + (currImage.getSize().y / 2), 20.0 * ((dir)? 1 : -1), 0.0, 0, PLAYER, false);

        //Scale the bullet
        shot->setScale(SCALE, SCALE);
        shot->hitBoxes[0]->height *= SCALE;
        shot->hitBoxes[0]->width *= SCALE;

        //Finish creating the bullet in the scene
        createObject(shot);
        shotTimer = 50;
        digitalShoot = true;

        playSound("./resources/r1/sound/shoot.wav");
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


    if(shotTimer - delta < shotTimer){
        shotTimer -= delta;
    } else {
        shotTimer = 0;
    }

    grounded = false;
}

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

Bullet::Bullet(float x, float y, float xSpeed, float ySpeed, int collisionLayer, unsigned int collisionFlags, bool grav):Object(x, y, collisionLayer, collisionFlags, grav){
    create(xSpeed, ySpeed);
}

void Bullet::onCollide(Object *other, int myBoxID, int otherBoxID){
    if(other->collisionFlags & GROUND){
        destroyObject(this);
    }
}

void Bullet::create(float xSpeed, float ySpeed){
    this->debug = false;
    this->collisionFlags |= PROJECTILE;
    this->friction = 0;
    this->xV = xSpeed;
    this->yV = ySpeed;
    
    setSprite((unsigned int)19);
	this->addHitBox(0,0,this->sprite->width,this->sprite->height);
}
