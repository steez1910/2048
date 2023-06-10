#include "game.hpp"
#include "assets.hpp"
#include <time.h>
#include <iostream>
#include <cstdlib>
// #include "32blit.hpp"
using namespace blit;

#define SCREEN_HEIGHT 240
#define SCREEN_WEIGHT 320
#define SQURE_SIZE 58


int MAP[4][4] = {
    {4, 4, 16, 0,},
	{2, 0, 0, 4},
	{2, 0, 32, 0},
	{0, 0, 128, 0},	
};
// numbers
Rect n0 = Rect(84,0,7,7);
Rect n2 = Rect(0,0,7,7);
Rect n4 = Rect(7,0,7,7);
Rect n8 = Rect(14,0,7,7);
Rect n16 = Rect(21,0,7,7);
Rect n32 = Rect(28,0,7,7);
Rect n64 = Rect(35,0,7,7);
Rect n128 = Rect(42,0,7,7);
Rect n256 = Rect(49,0,7,7);
Rect n512 = Rect(56,0,7,7);
Rect n1024 = Rect(63,0,7,7);
Rect n2048 = Rect(70,0,7,7);
Rect n4096 = Rect(77,0,7,7);

bool Moved = false;

///////////////////////////////////////////////////////////////////////////
void generateRandomNumber()
{
    uint x,y;
       do
    {
        x = rand() %4;
        y = rand() %4;
    } while (MAP[y][x] !=0);

    MAP[y][x]=2;
}
// void score()
// {
//     int score;
//     for ( int x = 0; x < 4; x++)
//     {
//         for (int y = 0; y < 4; y++)
//         {
//             score += MAP[y][x];
//         }
        
//     }
// }



void move(int x, int y, int X, int Y )
{   
    if (MAP[y][x] == 0 && MAP[y+Y][x+X] !=0)
    {   
        MAP[y][x] = MAP[y+Y][x+X];
        MAP[y+Y][x+X] = 0;
        Moved = true;
    }
        
    if (MAP[y][x] != 0 && MAP[y][x] == MAP[y+Y][x+X])
    {
        MAP[y][x] =  MAP[y][x] + MAP[y+Y][x+X];
        MAP[y+Y][x+X] = 0;
        Moved = true;
    }
    if (MAP[y][x] == MAP[y+Y][x+X] + MAP[y+Y+1][x+X] || MAP[y][x] == MAP[y+Y][x+X] + MAP[y+Y][x+X+1] )
    {
       MAP[y][x] = MAP[y][x];
       MAP[y+Y][x+X] = MAP[y+Y][x+X] + MAP[y+Y+1][x+X];
       MAP[y+Y+1][x+X] = MAP[y+Y+2][x+X];

    }
    
}

void moveUP()
{
    uint x,y;

    for (int i = 0; i < 3; i++)
    {
        for ( x = 0; x < 4; x++)
        {
            for ( y = 0; y < 3; y++)
            {
                move(x, y, 0 , 1);
            }
        }
    }
}   

void moveDown()
{   
    uint x,y;

    for (int i = 0; i < 3; i++)
    {
        for ( x = 0; x < 4; x++)
        {
            for ( y = 3; y > 0; y--)
            {
                move(x, y, 0 , -1);
            }
        
        }
    }
}

void moveLeft() 
{
    uint x,y;

    for (int i = 0; i < 3; i++)
    {
        for ( y = 0; y < 4; y++)
        {
            for ( x = 0; x < 3; x++)
            {
                move(x, y, 1 , 0);
            }
        }
    } 
}

void moveRight() 
{
    uint x,y;

    for (int i = 0; i < 3; i++)
    {
        for ( y = 0; y < 4; y++)
        {
            for ( x = 3; x > 0; x--)
            {
                move(x, y, -1 , 0);
            }
        }
    }
}

void init() {
    srand(time(0));
    set_screen_mode(ScreenMode::hires);
    screen.sprites = Surface::load(sheet);
    generateRandomNumber();
    generateRandomNumber();
}

void renderBackground(){
    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.clear();
}

///////////////////////////////////////////////////////////////////////////
//
// render(time)
//
// This function is called to perform rendering of the game. time is the 
// amount if milliseconds elapsed since the start of your game
//
void render(uint32_t time) {

    renderBackground();
    screen.pen = Pen(0, 0, 0);
  

     

    for (int y = 0; y < 4; y++) 
    {
        for (int x = 0; x < 4; x++)
        {
            if (MAP[y][x] == 0){ screen.sprite(n0, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 2){ screen.sprite(n2, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 4){screen.sprite(n4, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 8){screen.sprite(n8, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 16){screen.sprite(n16, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 32){screen.sprite(n32, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 64){screen.sprite(n64, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 128){screen.sprite(n128, Point(42 + x *SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 256){screen.sprite(n256, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 512){screen.sprite(n512, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 1024){screen.sprite(n1024, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 2048){screen.sprite(n2048, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 4096){screen.sprite(n4096, Point(42 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));} 
        }
        
    }
    
}

    
///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
    if (buttons.released & Button::DPAD_UP) 
    {
        moveUP();
        
    }
    if (buttons.released & Button::DPAD_DOWN)
    {
        moveDown();
    }
    if (buttons.released & Button::DPAD_LEFT)
    {
        moveLeft();
    }
    if (buttons.released & Button::DPAD_RIGHT )
    {
        moveRight();
    }
    if  (Moved) 
    {
        Moved = false;
        generateRandomNumber();

    }
}