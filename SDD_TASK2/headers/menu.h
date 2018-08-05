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
    void drawStringMemDefaultMenu(Graphics &graphicsObj);
    
    // pulse menu with restart and quit buttons 
    void drawTetrisStopMenu(Graphics &graphicsObj);
    void drawTetrisLoseMenu(Graphics &graphicsObj);

    void handleButtonEvent(SDL_Event &event, Process &process);
    void handleKeyboardEvent(SDL_Event &event);
    
    // just for Login::readUserDetailFromFile(), haha 作为传递介质(login->menu->game)
    void loadUserData();
    
    // this one if much more interesting，从(login->menu->game->tetris) used as an interface from Login class to Tetris class
    void getScoreFromGame(int value); // value is added to current user's score
    
    void writeToFile();
    
private:
    // a name for each button
    std::map<std::string, Button *> _buttons;
    
    Mix_Music *_bgm;
    Mix_Chunk *_mainBgm;
    Mix_Chunk *_tetrisBgm;
    Mix_Chunk *_buttonClickSound;
    Mix_Chunk *_tetrisGameOverSound;
    Mix_Chunk *_stringMemoryBgm;
    
    // for the look
    std::string _loginUserNameTypingStatusLook; // todo - 其实这个没用处，可以去掉
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
