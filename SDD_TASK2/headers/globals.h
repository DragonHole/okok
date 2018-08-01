//
//  globals.h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 6/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef globals_h
#define globals_h

// --------------General Globals------------------------------

namespace Globals{
    const int SCREEN_W = 400;       // these are the dimensions of the window in normal state(main menu)
    const int SCREEN_H = 400;
    
    const float SPRITE_SCALE = 1.0f;
    
    const float GAME_FPS = 30;
}

// namespace "Side" for side manipulation 
namespace Side{
    enum side{
        TOP, RIGHT, LEFT, DOWN, NONE
    };
    
// god-like algorithm
    inline side getOppositeSide(side Side){
        return Side == TOP ? DOWN :
        DOWN ? TOP :
        LEFT ? RIGHT :
        RIGHT ? LEFT :
        NONE;
    }
}

// object movement types
enum Direction{
    TOP, DOWN, LEFT, RIGHT
};

// different colors 
enum Color{
    RED, BLUE, GREEN, YELLOW
};

enum Scene{
    NONE,
    TETRIS_LOSE,
    TETRIS_WIN,
    
    STRINGMEM_LOSE
};

// set offsets for sprites, very handy little utility
struct Vector{
    int _x, _y;
    Vector():
    _x(0), _y(0) {}
    Vector(int x, int y):
    _x(x), _y(y){}
    
    Vector Vector0(){return Vector(0, 0);};
};

// what is showing on the screen(or running). main menu/tetris/option menu...etc
enum CurrentProcess{
    
};

// main menu dimensions
#define MAIN_MENU_WIDTH 736
#define MAIN_MENU_HEIGHT 552

// ----------------Game Specific Globals----------------------------
// Tetris
// No reason to be accessible outside this class
#define TETRIS_WINDOW_WIDTH 288 + 150             //
#define TETRIS_WINDOW_HEGHT 550                  // self-explanatory

// the specs of the game window
#define TETRIS_GAME_AREA_WIDTH 288             //
#define TETRIS_GAME_AREA_HEIGHT 550      //

// pause menu..
#define TETRIS_STOP_MENU_WIDTH 374
#define TETRIS_STOP_MENU_HEIGHT 406

#define TETRIS_LOSE_MENU_WIDTH 796
#define TETRIS_LOSE_MENU_HEIGHT 482

// dimensions for EVERY square 
#define TETRIS_SQUARE_HEIGHT 24
#define TETRIS_SQUARE_WIDTH 24
    
#define TETRIS_NUM_LEVEL 5                     // Number of levels
#define TETRIS_SCORE_PER_LINE 125              // amount of points scored for clearing one line
#define TETRIS_SCORE_NEEDED_PER_LEVEL 725
#define TETRIS_INITIAL_FALLING_SPEED 12         // level progresses with falling speed and ms to update, so both bigger distance and faster refresh
#define TETRIS_SPEED_CHANGE 0

#define TETRIS_MS_TO_UPDATE 800                // final ms to update = MS_TO_UPDATE - level* a constant
#define TETRIS_MS_TO_UPDATE_DIFFERENCE 100
    
    // in-game constants
#define TETRIS_SLIDE_TIME 15                   // sliding time when the block has reached the bottom
#define TETRIS_SQUARES_PER_ROW 10              //
#define TETRIS_SQUARES_PER_COL 20              //             //
    
    // constants for drawing screen elements
#define TETRIS_UI_NEXT_BLOCK_X  (612+155)       //
#define TETRIS_UI_NEXT_BLOCK_Y = 140            //
#define TETRIS_UI_SCORE_POSITION_X  (320)    //
#define TETRIS_UI_SCORE_POSITION_Y  (27)    //
#define TETRIS_UI_LEVEL_POSITION_X  (320)    //
#define TETRIS_UI_LEVEL_POSITION_Y  (107)         //
#define TETRIS_UI_SCORE_PER_LEVEL_X  (320)   //
#define TETRIS_UI_SCORE_PER_LEVEL_Y (197)         //
#define TETRIS_UI_SPEED_X	(612+60)            // falling speed of the current block
#define TETRIS_UI_SPEED_Y  320          // position of label drawing the current falling speed
#define TETRIS_UI_COMPLETED_LINES_X (320)
#define TETRIS_UI_COMPLETED_LINES_Y (287)
    
enum BlockType
{
    SQUARE_BLOCK,		// 正方形
    T_BLOCK,		// 反T形
    L_BLOCK,		// L形
    BACKWARDS_L_BLOCK,	// 反向L形
    LONG_BLOCK,		// 长方形
    S_BLOCK,		// S形
    BACKWARDS_S_BLOCK,	// 反向S形
};

// -------------------------------STRING-MEMORY--------------------------------
#define STRING_MEM_WINDOW_HEIGHT 584
#define STRING_MEM_WINDOW_WIDTH 1050

#define STRING_MEM_STOP_MENU_HEIGHT
#define STRING_MEM_STOP_MENU_WIDTH

#define STRING_MEM_SHOW_TIME 3000 // ms, although not accurate at all, you got the SDL_Delay() thing and other processes need some time to handle 
#define STRING_MEM_LEVEL_TIME_DIFF 

#define STRING_MEM_SCORE_EXTRA_CONSTANT 10   // give extra reward as level highers
#define STRING_MEM_SCORE_PER_LEVEL 50        // because only one question each level. Final score added = level*ScorePerLevel+level*constant

#endif /* globals_h */
