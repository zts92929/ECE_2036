
#include "mbed.h"
#include "dice.h"
#include "Farklegame.h"
#include "PinDetect.h"
#include "Speaker.h"
#include "MMA8452.h"

Serial pc(USBTX,USBRX);

//defines buttons for farklegame
PinDetect pb1(p21);
PinDetect pb2(p23); 
PinDetect pb3(p22);

//speaker that plays a note when rolling occurs
Speaker    myspeaker(p25);




int main()
{




pb1.mode(PullUp); 
pb2.mode(PullUp);
pb3.mode(PullUp);

 wait(.01);
 
MMA8452 acc(p28, p27, 40000);  //instantiate an acc object! 

//set parameters for accelerometer
acc.setBitDepth(MMA8452::BIT_DEPTH_12);
acc.setDynamicRange(MMA8452::DYNAMIC_RANGE_4G);
acc.setDataRate(MMA8452::RATE_100);

double x=0; // x,y,z planes for accelerometer to use
double y=0;
double z=0;
 
 // seeding for random number generator based on accelerometer value
acc.readXYZGravity(&x,&y,&z); //read z
z*=1000; 
z=static_cast<int>(z); // convert z to int since srand needs ints
srand(z);
Farklegame Farklegame1; // creation of farklegame

z=static_cast<double>(z); // reconvert back to double
z=0;


 

while(1){      
int trigger=0; //trigger to break out of loops
int trigger2=0; // trigger to break out if endturn is called
Farklegame1.startround();

while(trigger==0)
{
 acc.readXYZGravity(&x,&y,&z);
 if (x>0.65 || x<-0.65 || y>0.65|| y<-0.65) // check for shake
 {
     Farklegame1.RollDice(); // generates random numbers
     myspeaker.PlayNote(200.0,0.25,0.1); // plays a sound
     Farklegame1.CalcScore(); // calculates the score
     Farklegame1.displaydice(); // displays the score
     trigger=1; // break out of loop
}

else if (pb2==0) // check if B is pressed
{
    Farklegame1.changedice(); // change dice
}

 }
 
 trigger=0;
 
 
 while(trigger==0)
 {
 if (Farklegame1.getscore()==0) // if farkle, wait for A to be pushed then end turn
 {
     if (pb1==0)
     {
         Farklegame1.endturn();
         trigger=1;
         trigger2=1;
        }
}
 else
    {
        if (pb1==0)    // if button a then end turn
        {
         Farklegame1.endturn();
         trigger=1;
         trigger2=1;
        }
        else if(pb3==0)  // if button b, then store dice and return to start of round
        {
          Farklegame1.storedice();
          trigger=1;
        }
    }
}
if (trigger2==1) // if the play ended there turn, wait until A is pressed again
{
while(pb1==1)

{}
}
}

 
 

 
 } //main
