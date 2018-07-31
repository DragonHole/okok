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
#include "login.h"
#include "SDL2/SDL.h"
#include "SDL2_mixer/SDL_mixer.h"

// forward declare 
class Graphics;
class Process;

class Menu{
public:
    Menu();
    ~Menu();
    
    // draw menu(s), includes texts and images
    void drawMainMenu(Graphics &graphicsObj);
    void drawMainMenuCreateAccountMenu(Graphics &graphicsObj);
    void drawMainMenuLoginMenu(Graphics &graphicsObj);
    
    // basically only the stop button in the gaming-screen
    void drawTetrisDefaultMenu(Graphics &graphicsObj);
    
    // pulse menu with restart and quit buttons 
    void drawTetrisStopMenu(Graphics &graphicsObj);
    void drawTetrisLoseMenu(Graphics &graphicsObj);

    void handleButtonEvent(SDL_Event &event, Process &process);
    void handleKeyboardEvent(SDL_Event &event, Process &process);
    
    // just for Login::readUserDetailFromFile(), haha 作为传递介质(login->menu->game)
    void loadUserData();
    
    // this one if much more interesting，从(login->menu->game->tetris) used as an interface from Login class to Tetris class
    void getScoreFromGame(int value); // value is added to current user's score
    
private:
    // a name for each button
    std::map<std::string, Button *> _buttons;
    
    Mix_Music *_bgm;
    Mix_Chunk *_tetrisBgm;
    Mix_Chunk *_buttonClickSound;
    Mix_Chunk *_tetrisGameOverSound;
    
    // for the look
    std::string _loginUserNameTypingStatusLook;
    std::string _loginPasswordTypingStatusLook;
    
    // for acutal processing
    std::string _loginUsernameString;
    std::string _loginPasswordString;
    
    // current loged in user
    std::string _currentUser;
    
    // if user clicked on username space then this is set to 1, 2 if clicked on password space, otherwise 0(also default)
    int _clickedOnUsernameOrPassword;
    int _errorCode;
    int _isCredentialValid;
    
    Login _loginObj;
};

#endif /* menu_h */

// button index documentation
// TETRIS
// tetrisPauseButton
// tetrisStopMenuBackButton
