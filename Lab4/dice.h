#ifndef DICE_H
#define DICE_H

#include "mbed.h"
#include "uLCD_4DGL.h"

using namespace std;
uLCD_4DGL uLCD(p9, p10, p11); // serial tx, serial rx, reset pin;


class dice
{
    private:
    int num; // number rolled in die
    
    public:
    void rectangles(int x1,int y1,int x2, int y2)
    {
        //make a gray rectangle with a green outline
        uLCD.filled_rectangle(x1-2, y1-2 , x2+2, y2+2, GREEN);
        uLCD.filled_rectangle(x1,y1,x2,y2,LGREY);
        
        
    }
    void display_1(int x1,int y1,int x2,int y2)
    {
        // makes one circle in the place that it would on a one side
        uLCD.filled_circle(x1+19, y1+19 , 4, BLACK);
    }

    void display_2(int x1,int y1,int x2,int y2)
    {
        // makes two circles in the place that it would on a two side
        uLCD.filled_circle(x1+10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x2-10, y2-10 , 4, BLACK);
    }

    void display_3(int x1,int y1,int x2,int y2)
    {
        // makes three circles in the place that it would on a three side
        uLCD.filled_circle(x1+10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x1+19, y1+19 , 4, BLACK);
        uLCD.filled_circle(x2-10, y2-10 , 4, BLACK); 
    }    

    void display_4(int x1,int y1,int x2,int y2)
    {
        // makes four circles in the place that it would on a four side
        uLCD.filled_circle(x1+10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x2-10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x1+10, y2-10 , 4, BLACK);
        uLCD.filled_circle(x2-10, y2-10 , 4, BLACK);
    }


    void display_5(int x1, int y1,int x2,int y2)
    {
        // makes five circles in the place that it would on a five side
        uLCD.filled_circle(x1+10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x2-10, y1+10 , 4, BLACK);
        uLCD.filled_circle(x1+10, y2-10 , 4, BLACK);
        uLCD.filled_circle(x2-10, y2-10 , 4, BLACK);
        uLCD.filled_circle(x2-19, y2-19 , 4, BLACK);
    
        }

    void display_6(int x1,int y1,int x2,int y2)
    {
        // makes six circles in the place that it would on a six side
    uLCD.filled_circle(x1+9, y1+9 , 4, BLACK);
    uLCD.filled_circle(x2-9, y2-9 , 4, BLACK);
    uLCD.filled_circle(x1+9, y2-9 , 4, BLACK);
    uLCD.filled_circle(x2-9, y1+9 , 4, BLACK);
    uLCD.filled_circle(x1+9, y2-19 , 4, BLACK);
    uLCD.filled_circle(x2-9, y2-19 , 4, BLACK);
    
    }
    void circles(int x1,int y1,int x2,int y2, int num)
    {
    // calls a function to make circles depeneding on the number rolled
    switch(num)
    {
        case 1:
            display_1(x1,y1,x2,y2);
            break;
        case 2:
            display_2(x1,y1,x2,y2);
            break;
        case 3:
            display_3(x1,y1,x2,y2);
            break;
        case 4:
            display_4(x1,y1,x2,y2);
            break;
        case 5:
            display_5(x1,y1,x2,y2);
            break;
        case 6:
            display_6(x1,y1,x2,y2);
            break;
            
    }
       

}
    void rolldice()
    {
    //random number generator to simulate rolling dice
    num= rand() %6 +1;
    }
    //returns rolled number
    int getnum()
    {return (num);}
    
    

};

#endif