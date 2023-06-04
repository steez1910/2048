#include "game.hpp"
#include "assets.hpp"

using namespace blit;

#define SCREEN_HEIGHT 240
#define SCREEN_WEIGHT 320
#define SQURE_SIZE 58
///////////////////////////////////////////////////////////////////////////

// init()
//
// setup your game here
//
void init() {
    set_screen_mode(ScreenMode::hires);
    screen.sprites = Surface::load(two);
}

void renderBackground(){
    // clear the screen -- screen is a reference to the frame buffer and can be used to draw all things with the 32blit
    screen.clear();

    // draw some text at the top of the screen
    screen.alpha = 255;
    screen.mask = nullptr;
    screen.pen = Pen(196, 164, 132);
    screen.rectangle(Rect(0, 0, SCREEN_WEIGHT, SCREEN_HEIGHT));
    screen.pen = Pen(0, 0, 0);
    
    screen.rectangle(Rect(40, 0, 1, SCREEN_HEIGHT));
    screen.rectangle(Rect(279, 0, 1, SCREEN_HEIGHT));

    screen.rectangle(Rect(40, 0, SCREEN_HEIGHT, 1));
    screen.rectangle(Rect(40, 239, SCREEN_HEIGHT, 1));

    int startx = 41;
    int starty = 1;
    for (int i = 0; i < 3; i++) {
        screen.rectangle(Rect(startx + SQURE_SIZE, 0, 2, SCREEN_HEIGHT));
        screen.rectangle(Rect(40, starty + SQURE_SIZE, SCREEN_HEIGHT, 2));
        startx = startx + SQURE_SIZE + 2;
        starty = starty + SQURE_SIZE + 2;
    }

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
    screen.sprite(5, Point(50, 20));

    //screen.text("2048", minimal_font, Point(150, 5));
}

    
    
    // screen.pen = Pen(255, 255, 255);
    // screen.rectangle(Rect(240, 0, 80, 240));

    
///////////////////////////////////////////////////////////////////////////
//
// update(time)
//
// This is called to update your game state. time is the 
// amount if milliseconds elapsed since the start of your game
//
void update(uint32_t time) {
}