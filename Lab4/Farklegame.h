#ifndef FARKLEGAME_H
#define FARKLEGAME_H

#include "mbed.h"
#include "dice.h"

class Farklegame
{
    private:
        int numdice; //number of dice
        int maxdice; // maximum number of dice, in case of saved dice so you cannot roll too many
        int score;   // turn score
        int score2;  // roll score
        dice a[6];   // six dice for the game
        int arr[6];  // array of roll numbers
        int win;     // number of winning dice
        int farkles;  // number of farkles
        
    public:
        Farklegame();  // constructor
        void startround();  // starts the round
        void changedice();  // changes the dice
        void CalcScore();   // function that calculates the score
        void displaydice(); // function that displays the dice along with the current turn score and roll score
        void storedice();   // function that stores winning dice if the play wants to roll again
        void endturn();     // ends the turn
        void RollDice();    // calls a function in the dice class that "rolls" each of the dice
        int  getscore();    // returns the score
  
  
 };   
 
 Farklegame::Farklegame()
{
  // set initial values and create 6 dice
  numdice=6;  
  maxdice=6;
  score=0;
  farkles=0;
  score2=0;
  win=0;
  for (int i=0; i<6;i++)
  {
    dice objdice;
    a[i]=objdice;
  }
 
}

void Farklegame::startround()
{
  // display start screen with current die number
  uLCD.cls();
  uLCD.display_control(LANDSCAPE);
  uLCD.text_width(2);
  uLCD.text_height(2);
  uLCD.locate(0,1);
  uLCD.printf("Shake\n");
  uLCD.printf("Board\n");
  uLCD.printf("------\n");
  uLCD.printf("To\n");
  uLCD.printf("Roll\n");
  uLCD.printf("%d dice\n",numdice);
  
  }

void Farklegame::changedice()
{
    // changes the number of dice
    numdice=(numdice+1)%(maxdice+1);
}
void Farklegame::RollDice()
{
  // sets up the integer array of roll dice to be 0 at all numbers so dice from previous rolls cannot iterfere
  for (int i=0; i<6;i++)
   { arr[i]=0;}
  for(int i=0;i<numdice;i++)
  {
    // rolls the dice and puts the value into the integer array
    a[i].rolldice();
    arr[a[i].getnum()-1]+=1;
  }
 
}  

void Farklegame::CalcScore()
{
  
  int trigger=1; // trigger in case combination is found early
  int counter=0; // index for the integer array
  int numthree=0; // keeps track of number of threes in case there are two sets of them
  int numtwo=0;   // keeps track of number of twos in case there are three sets of them
  win=0; // number of winning dice
  if(arr[0]==1 && arr[1]==1 && arr[2]==1 && arr[3]==1 && arr[4]==1 && arr[5]==1)
  {
    // test to see if every number is rolled
    score+=1500;
    trigger=2;
    win=6;
  }
  while(trigger==1 && counter < 6)
  {
    int check=arr[counter];
    switch (check)
    {
     //switch to check the number of dice in each index of intarray
      case 6:
        //if there are six dice of one number change the score and break out of the while loop
        score+= 3000;
        trigger=0;
        win+=6;
        break;
      case 5:
      // if there are five dice of one number change the score and break out of the loop
        score+= 2000;
        trigger=0;
        win+=5;
        break;
      case 4:
      // if there are four dice of one number change the score and break out of the loop
        score+= 1000;
        trigger=0;
        win+=4;
        break;
      case 3:
      // if there are three dice of the same number, add 1000 if it is 3 ones otherwise add 100*number on dice,
      // if there are two sets of threes, change the score to 2500 and break out of the loop
        win+=3;
        if (numthree==1)
        {
          score=0;
          score+=2500;
          trigger=0;
        }
        else
        {
          if (counter==0)
          {
            score+=1000;
          }
          else{
            score+=(counter+1)*100;
          }
          numthree+=1;
        }
        break;
      case 2:
      // if there are three sets of twos, add 1500 and break out of the loop
        if (numtwo==2)
        {
          score+=1500;
          win+=6;
          for(int i=0;i<numdice;i++)
          {
            arr[i]=0;
          }
          trigger=0;
        }
        else
        {
          numtwo+=1;
        }
        break;
      }
      counter+=1;
    }
// add 50 for each 5 and 100 for each 1 assuming each of those number has less
// than three dice and the combination 1,2,3,4,5,6 is not there
  if(arr[0]<3 && trigger!=2)
  {
  score+=arr[0]*100;
  win+=arr[0];
  }
  if(arr[4]<3&& trigger!=2){
  score+=arr[4]*50;
  win+=arr[4];
  }
  score2=score-score2; // make score2 equal to the score of that roll
}

void Farklegame::displaydice()
{   
    // call a function in the dice class that displays the dice as a combination
    // of rectangles and circles x1,y1,x2,y2 represent the top left and bottom
    // right corners of the rectangles in pixles. The LCD display is 128x128
    uLCD.cls();
    int x1=7;
    int x2=45;
    int y1=10;
    int y2=48;
    for (int i=0;i<numdice;i++)
    {
    a[i].rectangles(x1,y1,x2,y2);
    a[i].circles(x1,y1,x2,y2,a[i].getnum());
    
    x1+=38;
    x2+=38;
    
    if (i==2)
        {
            x1=7;
            x2=45;
            y1+=48;
            y2+=48;
        }  
    }
    if (win>0)
    // if the play gets points display their points
    {
        uLCD.display_control(LANDSCAPE);
        uLCD.text_width(1);
        uLCD.text_height(1);
        uLCD.locate(0,14);
        uLCD.printf("Turn Score: %d\n",score);
        uLCD.printf("Roll Score: %d\n",score2);
    }
    else
    {
    // if the player farkles, print farkles and keep track of it, if there
    // are three farkles, change the score to -1000
        uLCD.display_control(LANDSCAPE);
        uLCD.text_width(1);
        uLCD.text_height(1);
        uLCD.locate(0,14);
        uLCD.printf("FARKLE\n");
        farkles+=1;
        score=0;
        if (farkles == 3)
        {
            score-=1000;
        }
        
     }   
    
}

void Farklegame::storedice()
{
    // store the winning dice
    numdice-=win;
    maxdice-=win;
    win=0;
}

void Farklegame::endturn()
{
    // display turn score, reset score and nubmer of dice
    uLCD.cls();
    uLCD.display_control(LANDSCAPE);
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.locate(0,1);
    uLCD.printf("Your\n");
    uLCD.printf("Turn\n");
    uLCD.printf("Score\n");
    uLCD.printf("------\n");
    uLCD.printf("%d\n", score);
    score=0;
    score2=0;
    numdice=6;
    maxdice=6;
}
//returns score
int Farklegame::getscore()
{return (score2);}

#endif