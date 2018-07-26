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
#include "rect.h"
#include "SDL2/SDL.h"

// this class shouldn't be called a class... just drawing menu UI

class Graphics;

class Menu{
public:
    Menu();
    ~Menu();
    
    // draw menu(s), includes texts and images
    void drawMainMenu(Graphics &graphicsObj);
    void drawTetrisMenu(Graphics &graphicsObj);
    void drawTetrisWinMenu(Graphics &graphicsObj);
    void drawTetrisLoseMenu(Graphics &graphicsObj);

    // clear this->_isButtonClicked at each new iteration of the game loop
    void refreshButtonState();
    
    // check the user input
    void checkButtonEvent(SDL_Event &event);
    
    // interface function: return true if a certain is pressed
    bool isButtonClicked(int index)const;
    
private:
    // clickable UI buttons
    std::map<int, Rect> _buttons;
    std::map<int, bool> _isButtonClicked;
};

#endif /* menu_h */

// button index documentation
// TETRIS
// 
