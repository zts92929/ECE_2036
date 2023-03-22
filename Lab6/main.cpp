#include "game.h"
#include <time.h>
#include "PinDetect.h"


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

int explosion[ASTEROID_HEIGHT * ASTEROID_WIDTH] = {
    r,r,_,_,r,_,r,r,_,R,_,_,R,r,_,
    R,R,r,r,_,R,r,r,R,_,_,r,r,R,_,
    r,_,r,R,r,R,r,_,R,_,r,R,_,r,r,
    _,r,R,R,R,R,R,R,_,R,R,R,_,R,_,
    r,r,r,_,R,R,_,R,R,R,R,R,R,R,r,
    _,r,R,R,_,R,R,R,R,_,R,R,r,r,_,
    r,R,r,R,R,R,_,R,R,R,R,R,_,r,r,
    _,_,R,R,R,R,R,R,_,R,R,R,r,R,_,
    _,R,r,r,R,_,R,R,R,R,r,r,R,r,_,
    r,r,r,R,_,R,R,r,R,_,R,_,_,_,r,
    r,r,_,_,r,r,R,R,r,_,_,r,R,_,_,
    _,_,_,r,_,_,r,r,r,_,_,_,r,r,_
};

uLCD_4DGL uLCD(p9, p10, p11); // instantiate a uLCD object
Serial pc(USBTX,USBRX); //not used, but must be defined to compile
MMA8452 acc(p28, p27, 40000);  //instantiate an acc object
Speaker mySpeaker(p25);
PinDetect pb1(p21);

bool overlap(ScreenObject & ship, ScreenObject & asteroid);
void explode(SpaceShipEarth ship);
void startDisplay();
void startGame();
void winningChime();

// Callback routine is interrupt activated by a debounced pb1 hit
void pb1_hit_callback (void)
{
    uLCD.cls();
    startGame();
}

int main() {
    pb1.mode(PullUp);
    uLCD.baudrate(300000);
    wait(0.2);

    pb1.attach_deasserted(&pb1_hit_callback);
    pb1.setSampleFrequency();  //default is 20KHz sampling
    srand(time(0)); // do this srand call here ONLY... no where else in the code!

    startGame();
}

// Global function that "runs" the game

void startGame()
{
    set_time(1256729737);
    ScreenObject * ActiveAsteroids[NUM_ASTEROIDS];
    ActiveAsteroids[0] = new ConcreteAsteroid1;
    ActiveAsteroids[1] = new ConcreteAsteroid2;
    ActiveAsteroids[2] = new ConcreteAsteroid3;
    ActiveAsteroids[3] = new ConcreteAsteroid4;


    startDisplay();

    // Display ScreenObjects' initial positions
    SpaceShipEarth ship;
    ship.draw();

    for (int i = 0; i < NUM_ASTEROIDS; i++) {
        ActiveAsteroids[i]->draw();
    }

    // Setup game variables
    bool gameOver = false;

    time_t startTime = time(0);
    time_t timeNow = time(0);
    double timeElapsed = 0;

    while (!gameOver)
    {
        for (int i = 0; i < NUM_ASTEROIDS; i++) {
            ActiveAsteroids[i]->update();
        }
        ship.update();

        // Update time and calculate timeElapsed
        timeNow = time(0);
        timeElapsed = timeNow-startTime;

        if (timeElapsed < 30)
        {
        uLCD.filled_rectangle(3, 0, 120, 3, BLACK);
        uLCD.filled_rectangle(3, 0, static_cast<int>(120 - 4 * timeElapsed), 3, BLUE);  // 120 pixels per 30 seconds means a decrement of 4 pixels every second
        }
        else if (timeElapsed > 30)
        {
            uLCD.cls();
            uLCD.locate(6,6);
            uLCD.printf("YOU WIN!");
            winningChime();
            gameOver = true;
        }

        for (int i = 0; i < NUM_ASTEROIDS; i++) {
            if (overlap(ship, *ActiveAsteroids[i]))
            {
                gameOver = true;
                explode(ship);
            }
        }
    }
}

// Global collision detection funciton
bool overlap(ScreenObject & ship, ScreenObject & asteroid)
{
    return ((ship.getX()+ EARTH_WIDTH) >= asteroid.getX() && (asteroid.getX() + ASTEROID_WIDTH) >= ship.getX() && (ship.getY() + EARTH_WIDTH) >= asteroid.getY() && (asteroid.getY() + ASTEROID_WIDTH) >= ship.getY());
}

// Global explode function for when asteroid collides with ship
void explode(SpaceShipEarth ship) {
    uLCD.BLIT(ship.getX(), ship.getY(), ASTEROID_WIDTH, ASTEROID_HEIGHT, explosion);
    uLCD.locate(6,6);
    uLCD.printf("GAME OVER");
    for (int i=500; i>=100; i=i-200) {
        mySpeaker.PlayNote(i, 0.4,0.05);
    }
}

// Beginning display screen function
void startDisplay() {
    uLCD.text_bold('\x76');
    uLCD.locate(6,6);
    uLCD.printf("Survive\n");
    uLCD.printf("for 30\n");
    uLCD.printf("Seconds!!\n");
    mySpeaker.PlayNote(600, 0.2,0.05);
    mySpeaker.PlayNote(700, 0.2,0.05);
    mySpeaker.PlayNote(700, 0.2,0.05);
    mySpeaker.PlayNote(800, 0.2,0.05);
    mySpeaker.PlayNote(800, 0.2,0.05);
    mySpeaker.PlayNote(800, 0.2,0.05);
    mySpeaker.PlayNote(800, 0.2,0.05);
    mySpeaker.PlayNote(1000, 0.2,0.05);
    mySpeaker.PlayNote(1000, 0.2,0.05);
    wait(0.5);
    uLCD.cls();
}

// Plays a chime when the player wins
void winningChime() {
    for (int i=1000; i<3000; i=i+400) {
        mySpeaker.PlayNote(i, 0.15,0.05);
    }
}
