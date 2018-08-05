//
//  game .h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 22/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef game__h
#define game__h

#include "tetris.h"
#include "keyboard.h"
#include "graphics.h"
#include "process.h"
#include "menu.h"
#include "stringMemory.h"
#include "match_n_see.h"

// further encapsulation
// right below main

class Game{
public:
    Game();
    ~Game();
    
    void loop();
    
    void update(double elapsedTime);
    
// by-reference may slightly improve performance, although it is negligible. because the object to pass is so small
    void handleInput();
    
    void draw(double elapsedTime);
    
private:
    SDL_Event _event;
    Process _process;
    Graphics _graphicsObj;
    Keyboard _keyboardObj;
    Menu _menuObj;

    Tetris _tetrisObj;
    stringMemory _stringMemoryObj;
    match_n_see _match_n_seeObj;
    
    // just for Menu::getScoreFromGame(), yea.. what a shame, bad:(
    bool _loaded;
    bool _loaded2;
    Scene _which;
    
    double _timeElapsed;
};

#endif /* game__h */
