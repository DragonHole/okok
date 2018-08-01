//
//  stringMemory.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 31/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef stringMemory_h
#define stringMemory_h

#include <iostream>
#include "globals.h"
#include "SDL2/SDL.h"
#include "button.h"
#include "process.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "SDL2_mixer/SDL_mixer.h"

// second unit, prints a string to the screen for few seconds and asks the player to replicate with keyboard

class Graphics;

class stringMemory{
public:
    stringMemory();
    
    ~stringMemory();
    
    Scene update(Graphics &graphicsObj, double timeElapsed);
    
    void handleButtonEvent(SDL_Event &event);
    
    void handleKeyboardEvent(SDL_Event &event);
    
    void genNewString();
    
    void draw(Graphics &graphicsObj);
    
private:
    std::string _currentString;     // the required string 
    std::string _userString;        // what the user inputs
    int _correct; // 0-none, 1-correct, 2-incorrect
    
    int _level;
    int _score;
    
    bool _gameOverTrue;
    bool _started;      // only start when the user clicked on the start button
    
    Button *_startButton;
    SDL_Color _color;
    
    TTF_Font *_font;
    
    Mix_Chunk *_bingoSound;
    Mix_Chunk *_wrongSound;
    Mix_Chunk *_clickButtonSound;
};

#endif /* stringMemory_h */
