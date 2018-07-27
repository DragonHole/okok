//
//  menu.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 20/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef menu_h
#define menu_h

#include <map>
#include "button.h"
#include "SDL2/SDL.h"

// forward declare 
class Graphics;
class Process;

class Menu{
public:
    Menu();
    ~Menu();
    
    // draw menu(s), includes texts and images
    void drawMainMenu(Graphics &graphicsObj);
    
    // basically only the stop button in the gaming-screen
    void drawTetrisDefaultMenu(Graphics &graphicsObj);
    
    // pulse menu with restart and quit buttons 
    void drawTetrisStopMenu(Graphics &graphicsObj);
    void drawTetrisWinMenu(Graphics &graphicsObj);
    void drawTetrisLoseMenu(Graphics &graphicsObj);

    void handleButtonEvent(SDL_Event &event, Process &process);
    
private:
    // a name for each button
    std::map<std::string, Button *> _buttons;
};

#endif /* menu_h */

// button index documentation
// TETRIS
// 
