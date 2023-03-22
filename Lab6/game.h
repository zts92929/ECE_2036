#include "mbed.h"
#include "uLCD_4DGL.h"
#include "MMA8452.h"
#include "Speaker.h"

#ifndef game_h
#define game_h

class ScreenObject 
{
protected:
    int xPos;
    int yPos; 
public:
    int getX() const;
    int getY() const;
    virtual void draw()=0;
    virtual void update()=0;
};

class SpaceShipEarth : public ScreenObject
{
public:
    SpaceShipEarth();
    void draw();
    void update();
};

class AbstractAsteroid : public ScreenObject 
{
public:
    void randPos();
    void randSlope();
protected:
    int deltaX;
    int deltaY;
};

class ConcreteAsteroid1 : public AbstractAsteroid
{
public:
    ConcreteAsteroid1();
    void draw();
    void update();
};

class ConcreteAsteroid2 : public AbstractAsteroid
{
public:
    ConcreteAsteroid2();
    void draw();
    void update();
};

class ConcreteAsteroid3 : public AbstractAsteroid
{
public:
    ConcreteAsteroid3();
    void draw();
    void update();
};

class ConcreteAsteroid4 : public AbstractAsteroid
{
public:
    ConcreteAsteroid4();
    void draw();
    void update();
};

#endif /* game_h */