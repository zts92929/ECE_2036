#include "game.h"

#define ASTEROID_HEIGHT 12
#define ASTEROID_WIDTH 15
#define SPRITE_MAX 15
#define EARTH_WIDTH 10
#define EARTH_HEIGHT 10
#define EXPLOSION1_WIDTH 20

#define SCREEN_MAX 125
#define SCREEN_MIN 1
#define NUM_ASTEROIDS 4

#define Q 0x808000 //OLIVE
#define I 0x008000 //GREEN
#define S 0xC0C0C0 //SILVER
#define C 0x17202A //UFO GLASS
#define D 0x797D7F //DARK GREY
#define L 0x00FF00 //LIME
#define P 0xFF00FF //PINK
#define R 0xF1C40F //YELLOW
#define O 0xF39C12 //ORANGE
#define G 0xAAB7B8 //GREY
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE
#define B 0x0000FF //BLUE
#define r 0xFF0000 //RED

extern uLCD_4DGL uLCD;
extern Serial pc;
extern MMA8452 acc;
extern Speaker mySpeaker;

// Gloabl Functions

int asteroid_sprite_1[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,X,X,X,X,X,X,X,X,_,_,_,
    _,_,_,X,_,_,_,_,_,_,_,_,X,_,_,
    _,_,X,_,_,_,_,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,_,_,_,X,_,_,
    X,X,X,X,_,_,_,_,_,_,_,_,_,X,_,
    _,_,_,X,_,_,_,_,_,_,_,_,_,X,_,
    _,_,X,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,X,_,_,_,_,_,X,_,
    X,_,_,_,_,_,X,X,_,_,_,_,X,_,_,
    _,X,_,_,_,X,_,X,_,_,_,_,X,_,_,
    _,_,X,_,X,_,_,X,_,_,_,X,_,_,_,
    _,_,_,X,_,_,_,X,X,X,X,_,_,_,_
};

int asteroid_sprite_2[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,_,_,X,X,X,X,X,_,_,_,_,
    _,_,_,_,_,_,X,_,_,_,X,_,_,_,_,
    _,_,_,_,_,X,_,_,_,_,X,_,_,_,_,
    _,_,_,X,X,_,_,_,_,_,X,_,_,_,_,
    X,X,X,_,_,_,_,_,_,_,X,X,X,X,_,
    X,_,_,_,_,_,_,_,_,_,_,_,_,X,_,
    X,_,_,_,_,_,_,_,_,_,_,_,_,X,_,
    X,_,_,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,X,_,_,_,_,_,_,_,_,_,X,X,_,
    _,_,_,X,_,_,_,_,X,X,X,X,_,_,_,
    _,_,_,X,_,_,_,X,_,_,_,_,_,_,_,
    _,_,_,X,X,X,X,_,_,_,_,_,_,_,_
};

int asteroid_sprite_3[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,_,X,X,X,X,X,X,_,_,_,_,
    _,_,_,_,X,_,_,_,_,_,_,X,_,_,_,
    _,_,_,X,_,_,_,_,_,_,_,_,X,_,_,
    _,_,X,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,_,X,
    X,_,_,_,_,_,_,_,_,_,_,_,_,_,X,
    X,_,_,_,_,_,_,_,_,_,_,_,_,_,X,
    X,_,_,_,_,_,_,_,_,_,X,_,_,_,X,
    X,_,_,X,X,_,_,_,_,X,_,X,_,X,_,
    X,_,X,_,X,_,_,_,_,X,_,_,X,_,_,
    X,X,_,_,X,_,_,_,_,X,_,_,_,_,_,
    _,_,_,_,X,X,X,X,X,X,_,_,_,_,_
};

int asteroid_sprite_4[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    _,_,_,_,_,_,_,_,_,X,X,_,_,_,_,
    _,_,_,_,X,X,_,_,X,_,_,X,X,_,_,
    _,_,_,X,_,_,X,X,_,_,_,_,_,X,_,
    _,_,X,_,_,_,_,_,_,_,_,_,X,_,_,
    _,X,_,_,_,_,_,_,_,_,_,X,_,_,_,
    _,_,X,_,_,_,_,_,_,_,_,_,X,_,_,
    _,_,_,X,_,_,_,_,_,_,_,_,_,X,_,
    _,_,X,_,_,_,_,_,_,_,_,_,_,X,_,
    _,X,_,_,_,_,_,_,_,_,_,_,_,X,_,
    _,_,X,_,_,_,_,_,_,X,_,_,X,_,_,
    _,X,X,X,X,X,_,_,X,_,X,_,X,_,_,
    _,_,_,_,_,_,X,X,_,_,_,X,_,_,_
};

int blank_asteroid[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,
_,_,_,_,_,_,_,_,_,_,_,_,_,_,_
};

int spaceship_earth1[EARTH_WIDTH *EARTH_HEIGHT] = {
    _,_,S,S,S,S,S,S,_,_,
    _,S,I,I,I,I,I,I,S,_,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    S,I,I,I,I,I,I,I,I,S,
    _,S,I,I,I,I,I,I,S,_,
    _,_,S,S,S,S,S,S,_,_
};

int blank_ship[EARTH_WIDTH *EARTH_HEIGHT] = {
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_,
    _,_,_,_,_,_,_,_,_,_
};

// Screen Object

int ScreenObject::getX() const {
    return xPos;
}

int ScreenObject::getY() const {
    return yPos;
}

// Space Ship

SpaceShipEarth::SpaceShipEarth() {
    xPos = 64;
    yPos = 64;
}

void SpaceShipEarth::draw()
{
    uLCD.BLIT(xPos, yPos, EARTH_WIDTH, EARTH_HEIGHT, spaceship_earth1);
}

void SpaceShipEarth::update()
{
    double x = 0;
    double y = 0;
    double z = 0;
    int rate = 35;
    int xBefore = xPos;
    int yBefore = yPos;
    if(!acc.isXYZReady())
      {
         wait(0.01);
      }
      else
      {

        acc.readXYZGravity(&x,&y,&z);
        if ((xPos +(int)(rate*y) + EARTH_WIDTH < SCREEN_MAX) && (xPos + (int)(rate*y)>= SCREEN_MIN))
        {
            xPos += (int)(rate*y);
        }
        if((yPos +(int)(rate*x) + EARTH_HEIGHT < SCREEN_MAX) && (yPos + (int)(rate*x)>= 4))
        {
            yPos += (int)(rate*x);
        }
        if((xPos != xBefore) or (yPos != yBefore))  // If position hasn't changed, no need to clear position
        {
            uLCD.BLIT(xBefore, yBefore, EARTH_WIDTH, EARTH_HEIGHT, blank_ship);
        }
        draw();
      }
}

// Abstract Asteroid

void AbstractAsteroid::randPos()
{
    int side = rand()%4; // determines which side the asteroid enters
    switch(side) {
        case 0: // top
            xPos = rand() % (SCREEN_MAX - ASTEROID_WIDTH) + SCREEN_MIN;
            yPos = SCREEN_MIN;
            break;
        case 1: // left
            xPos = SCREEN_MIN;
            yPos = rand() % (SCREEN_MAX - ASTEROID_HEIGHT) + SCREEN_MIN;
            break;
        case 2: // right
            xPos = SCREEN_MAX - ASTEROID_WIDTH;
            yPos = rand() % (SCREEN_MAX - ASTEROID_HEIGHT) + SCREEN_MIN;
            break;
        case 3: // bottom
            xPos = rand() % (SCREEN_MAX - ASTEROID_WIDTH) + SCREEN_MIN;
            yPos = SCREEN_MAX - ASTEROID_HEIGHT;
            break;
    }
}

void AbstractAsteroid::randSlope()
{
    int tempX = rand() % 4 + 2;
    int tempY = rand() % 4 + 2;

    // Assign slope for top position
    if (yPos == SCREEN_MIN and xPos <= ((SCREEN_MAX - ASTEROID_WIDTH)/2)) {
        deltaX = tempX;
        deltaY = tempY;
    }
    else if (yPos == SCREEN_MIN and xPos > ((SCREEN_MAX - ASTEROID_WIDTH)/2)) {
        deltaX = -tempX;
        deltaY = tempY;
    }

    // Assign slope for bottom position
    else if (yPos == (SCREEN_MAX - ASTEROID_HEIGHT) and xPos <= ((SCREEN_MAX - ASTEROID_WIDTH)/2)) {
        deltaX = tempX;
        deltaY = -tempY;
    }
    else if (yPos == (SCREEN_MAX - ASTEROID_HEIGHT)and xPos > ((SCREEN_MAX - ASTEROID_WIDTH)/2)) {
        deltaX = -tempX;
        deltaY = -tempY;
    }

    // Assign slope for Left position
    else if (yPos <= ((SCREEN_MAX - ASTEROID_HEIGHT)/2) and xPos == SCREEN_MIN) {
        deltaX = tempX;
        deltaY = tempY;
    }
    else if (yPos > ((SCREEN_MAX - ASTEROID_HEIGHT)/2) and xPos == SCREEN_MIN) {
        deltaX = tempX;
        deltaY = -tempY;
    }

    // Assign slope for Right position
    else if (yPos <= ((SCREEN_MAX - ASTEROID_HEIGHT)/2) and xPos == (SCREEN_MAX - ASTEROID_WIDTH)) {
        deltaX = -tempX;
        deltaY = tempY;
    }
    else if (yPos > ((SCREEN_MAX - ASTEROID_HEIGHT)/2) and xPos == (SCREEN_MAX - ASTEROID_WIDTH)) {
        deltaX = -tempX;
        deltaY = -tempY;
    }
}

// Concrete Asteroids section

ConcreteAsteroid1::ConcreteAsteroid1() {
    this->randPos();
}

void ConcreteAsteroid1::draw() {
    uLCD.BLIT(xPos,yPos,ASTEROID_WIDTH,ASTEROID_HEIGHT,asteroid_sprite_1);
}

void ConcreteAsteroid1::update()
{
    int xBefore = xPos;
    int yBefore = yPos;

    // Updates x position
    if ((xPos + deltaX) >= SCREEN_MIN and (xPos + deltaX) <= (SCREEN_MAX + 2 - ASTEROID_WIDTH)) {
        xPos += deltaX;
    }
    else {
        this->randPos();
        this->randSlope();
    }

    // Updates y position
    if ((yPos + deltaY) >= SCREEN_MIN and (yPos + deltaY) <= (SCREEN_MAX + 2 - ASTEROID_HEIGHT)) {
        yPos += deltaY;
    }
    else {
        this->randPos();
        this->randSlope();
    }
    uLCD.BLIT(xBefore, yBefore, ASTEROID_WIDTH, ASTEROID_HEIGHT, blank_asteroid);
    draw();
}

ConcreteAsteroid2::ConcreteAsteroid2() {
    this->randPos();
}

void ConcreteAsteroid2::draw() {
    uLCD.BLIT(xPos,yPos,ASTEROID_WIDTH,ASTEROID_HEIGHT,asteroid_sprite_2);
}

void ConcreteAsteroid2::update()
{
    int xBefore = xPos;
    int yBefore = yPos;

    if ((xPos + deltaX) >= SCREEN_MIN and (xPos + deltaX) <= (SCREEN_MAX + 2 - ASTEROID_WIDTH)) {
        xPos += deltaX;
    }
    else {
        this->randPos();
        this->randSlope();
    }

    if ((yPos + deltaY) >= SCREEN_MIN and (yPos + deltaY) <= (SCREEN_MAX + 2 - ASTEROID_HEIGHT)) {
        yPos += deltaY;
    }
    else {
        this->randPos();
        this->randSlope();
    }
    uLCD.BLIT(xBefore, yBefore, ASTEROID_WIDTH, ASTEROID_HEIGHT, blank_asteroid);
    draw();
}

ConcreteAsteroid3::ConcreteAsteroid3() {
    this->randPos();
}

void ConcreteAsteroid3::draw() {
    uLCD.BLIT(xPos,yPos,ASTEROID_WIDTH,ASTEROID_HEIGHT,asteroid_sprite_3);
}

void ConcreteAsteroid3::update()
{
    int xBefore = xPos;
    int yBefore = yPos;

    if ((xPos + deltaX) >= SCREEN_MIN and (xPos + deltaX) <= (SCREEN_MAX + 2 - ASTEROID_WIDTH)) {
        xPos += deltaX;
    }
    else {
        this->randPos();
        this->randSlope();
    }

    if ((yPos + deltaY) >= SCREEN_MIN and (yPos + deltaY) <= (SCREEN_MAX + 2 - ASTEROID_HEIGHT)) {
        yPos += deltaY;
    }
    else {
        this->randPos();
        this->randSlope();
    }
    uLCD.BLIT(xBefore, yBefore, ASTEROID_WIDTH, ASTEROID_HEIGHT, blank_asteroid);
    draw();
}

ConcreteAsteroid4::ConcreteAsteroid4() {
    this->randPos();
}

void ConcreteAsteroid4::draw() {
    uLCD.BLIT(xPos,yPos,ASTEROID_WIDTH,ASTEROID_HEIGHT,asteroid_sprite_4);
}

void ConcreteAsteroid4::update()
{
    int xBefore = xPos;
    int yBefore = yPos;

    if ((xPos + deltaX) >= SCREEN_MIN and (xPos + deltaX) <= (SCREEN_MAX + 2 - ASTEROID_WIDTH)) {
        xPos += deltaX;
    }
    else {
        this->randPos();
        this->randSlope();
    }

    if ((yPos + deltaY) >= SCREEN_MIN and (yPos + deltaY) <= (SCREEN_MAX + 2 - ASTEROID_HEIGHT)) {
        yPos += deltaY;
    }
    else {
        this->randPos();
        this->randSlope();
    }
    uLCD.BLIT(xBefore, yBefore, ASTEROID_WIDTH, ASTEROID_HEIGHT, blank_asteroid);
    draw();
}
