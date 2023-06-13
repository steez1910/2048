#include "game.hpp"
#include "assets.hpp"

// #include "32blit.hpp"
using namespace blit;

#define SCREEN_HEIGHT 240
#define SCREEN_WEIGHT 320
#define SQURE_SIZE 58


int MAP[4][4] = {0
    // {2, 2, 8, 16,},
	// {16, 2, 4, 8},
	// {2, 4, 8, 16},
	// {16, 4, 4, 8},	
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
 int SCORE = 0;
 int MOVES = 0;

///////////////////////////////////////////////////////////////////////////
void generateRandomNumber()
{
    //1 - limit the loop
    //2 - generate 2 and 4
    //3 - 4 is rare
    // int val = blit::random() % 2 == 0 ? 2 : 4;
    int val;
    uint x,y;

    if  ((blit::random() % 10) < 9)
    {
        val=2;
    }
    else 
    {
        val=4;
    }

    for (int i = 0; i < 21; i++)
    {
        x = blit::random() % 4;
        y = blit::random() % 4;
        if  (MAP[y][x] == 0) {
                MAP[y][x] = val;
                return;
        }
    }

    for (x = 0; x < 4; x++)
    {
        for (y = 0; y < 4; y++)
        {
            if  (MAP[y][x] == 0) {
                MAP[y][x] = val;
                return;
            }
        }
    }       

} 
void statistics()
{
  screen.pen = Pen(255, 255, 255);
  screen.text("Score: " + std::to_string(SCORE),  minimal_font, Point(255, 30));
  screen.text("Moves: " + std::to_string(MOVES),  minimal_font, Point(255, 45));

}   

void swap( int *a, int *b )
{
   int tmp = *a;
   *a = *b;
   *b = tmp;;
}

void pushZerosEndRaw(int y, int direction){
    int FirstNonZero;

    if (direction == 1)
    {
        FirstNonZero = 0;

        for (int x = 0; x < 4; x++)
        {
            if  (MAP[y][x] !=0)
            {
                if  (x != FirstNonZero)
                {
                    Moved = true;
                    swap(&MAP[y][x], &MAP[y][FirstNonZero]);
                }
                FirstNonZero ++; 
                
            } 
        }
    }
    else 
    {
        FirstNonZero = 3;

        for (int x = 3; x >= 0; x--)
        {
            if  (MAP[y][x] !=0)
            {
                if  (x != FirstNonZero)
                {
                    Moved = true;
                    swap(&MAP[y][x], &MAP[y][FirstNonZero]);
                }
                FirstNonZero --;
            } 
                    
        }  
    }
}
void pushZerosColumn(int x, int direction)
{
    if (direction == 1)
    {
        int FirstNonZero = 0;

        for ( int y = 0; y < 4; y++)
        {
            if  (MAP[y][x] !=0)
            {
                if  (y != FirstNonZero)
                {
                    Moved = true;
                    swap(&MAP[y][x], &MAP[FirstNonZero][x]);
                }
                
                FirstNonZero ++;
            } 
        }
    }
    else 
    {
         int FirstNonZero = 3;

        for ( int y = 3; y >= 0; y--)
        {
            if  (MAP[y][x] !=0)
            {
                if  (y != FirstNonZero)
                {
                    Moved = true;
                    swap(&MAP[y][x], &MAP[FirstNonZero][x]);
                }            
                FirstNonZero --;
            } 
        }

    }
}

void pushZerosDown()
{
    for (int x = 0; x < 4; x++)
    {
        pushZerosColumn(x,0);
    }
}

void pushZerosTop()
{
    for (int x = 0; x < 4; x++)
    {
        pushZerosColumn(x,1);
    }
}

void pushZerosLeft()
{
    for (int y = 0; y < 4; y++)
    {
        pushZerosEndRaw(y,1);
    }
}

void pushZeroRight()
{
    for ( int y = 0; y < 4; y++)
    {
        pushZerosEndRaw(y,0);
    }
}

void plus(int x, int y, int X, int Y )
{
    if (MAP[y][x] != 0 && MAP[y][x] == MAP[y+Y][x+X])
    {
        MAP[y][x] =  MAP[y][x] + MAP[y+Y][x+X];
        MAP[y+Y][x+X] = 0; 
        Moved = true; 
        SCORE += MAP[y][x] + MAP[y+Y][x+X];
    } 
}

void plusUP()
{
    uint x,y;

    for ( x = 0; x < 4; x++)
    {
        for ( y = 0; y < 3; y++)
        {
            plus(x, y, 0 , 1);
        }
    }
    
}   

void plusDown()
{
    uint x,y;

    for ( x = 0; x < 4; x++)
    {
        for ( y = 0; y < 4; y++)
        {
            plus(x, y, 0 , -1);
        }
    }
    
}
void plusLeft()
{
    uint x,y;

    for ( y = 0; y < 4; y++)
        {
            for ( x = 0; x < 3; x++)
            {
                plus(x, y, 1 , 0);
            }
        }
} 

void plusRight()
{
    uint x,y;

    for ( y = 0; y < 4; y++)
        {
            for ( x = 3; x > 0; x--)
            {
                plus(x, y, -1 , 0);
            }
        }
}



void init() {
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
    screen.rectangle(Rect(0, 0, 320, 240));
  

    statistics();

    for (int y = 0; y < 4; y++) 
    {
        for (int x = 0; x < 4; x++)
        {
            if (MAP[y][x] == 0){ screen.sprite(n0, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 2){ screen.sprite(n2, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 4){screen.sprite(n4, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 8){screen.sprite(n8, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 16){screen.sprite(n16, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 32){screen.sprite(n32, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 64){screen.sprite(n64, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 128){screen.sprite(n128, Point( 4 + x *SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 256){screen.sprite(n256, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 512){screen.sprite(n512, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 1024){screen.sprite(n1024, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 2048){screen.sprite(n2048, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));}
            if (MAP[y][x] == 4096){screen.sprite(n4096, Point( 4 + x * SQURE_SIZE, 2 + y * SQURE_SIZE));} 
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
    Moved = false;
    if (buttons.released & Button::DPAD_UP) 
    {
        pushZerosTop();
        plusUP();
        pushZerosTop();  
    }
    if (buttons.released & Button::DPAD_DOWN)
    {
        pushZerosDown();
        plusDown();
        pushZerosDown();
    }
    if (buttons.released & Button::DPAD_LEFT)
    {
        pushZerosLeft();
        plusLeft();
        pushZerosLeft();
    }
    if (buttons.released & Button::DPAD_RIGHT )
    {
        pushZeroRight();
        plusRight();
        pushZeroRight();
    }
    if  (Moved) 
    {
        MOVES ++;
        Moved = false;
        generateRandomNumber();

    }
}