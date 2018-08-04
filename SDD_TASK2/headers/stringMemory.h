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
    
    void genString();
    
    void draw(Graphics &graphicsObj);
    
    void reset();
    
    int getScore()const;
private:
    std::string _currentString;     // the required string
    std::string _incrementCurrentString;
    std::string _userString;        // what the user inputs
    std::string _statusString;
    
    char _alpha[36]= {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
    
    int _correct; // 0-none, 1-correct, 2-incorrect
    
    int _level;
    int _score;
    
    double _elapsedTime;   // amount of ms the text is shown 
    
    bool _gameOverTrue;
    bool _started;      // only start when the user clicked on the start button
    bool _hint;
    bool _exit;
    bool _save;
    
    Button *_startButton;
    Button *_replayButton;
    Button *_hintButton;
    Button *_exitButton;
    Button *_saveButton;
//    Button *_submitButton;  // deprecated, use enter button instead 
    
    SDL_Color _color;
    SDL_Color _redColor;
    TTF_Font *_font;
    
    Mix_Chunk *_bingoSound;
    Mix_Chunk *_wrongSound;
    Mix_Chunk *_clickButtonSound;
};

#endif /* stringMemory_h */
