//
//  stringMemory.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 31/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "stringMemory.h"
#include "graphics.h"
#include "globals.h"

stringMemory::stringMemory():_currentString(""), _gameOverTrue(false), _started(false), _correct(0){
    // text color
    this->_color = {0, 0, 0};
    
    this->_startButton = new Button("stringMemStartButton1.png", "stringMemStartButton2.png", 200, 200, 460, 85);
    
    this->_font = TTF_OpenFont("font2.ttf", 36);
    
    this->_bingoSound = Mix_LoadWAV("stringMemBingoSound.wav");
    this->_wrongSound = Mix_LoadWAV("stringMemWrongSound.wav");
    this->_clickButtonSound = Mix_LoadWAV("stringMemButtonSound.wav");
}

stringMemory::~stringMemory(){}

Scene stringMemory::update(Graphics &graphicsObj, double timeElapsed){

    if(_started && _correct == 1){
        
    }
    
    if(this->_gameOverTrue)
        return Scene::STRINGMEM_LOSE;
    
    return Scene::NONE;
}

void stringMemory::handleButtonEvent(SDL_Event &event){
    this->_startButton->update(event);
    if(this->_startButton->isButtonClicked()){
        Mix_PlayChannel(-1, this->_clickButtonSound, 0);
        this->_started = true;
    }
    
}

void stringMemory::handleKeyboardEvent(SDL_Event &event){
    // if enter is pressed, then check for validity and go on
    if(event.key.keysym.scancode == SDL_SCANCODE_RETURN){
        if(this->_userString == this->_currentString){
            Mix_PlayChannel(-1, this->_bingoSound, 0);
            _correct = 1;
        }
        else{
            Mix_PlayChannel(-1, this->_wrongSound, 0);
            _correct = 2;
        }
    }
    
    if(strlen(this->_userString.c_str()) < 20 && this->_started)
        this->_userString += (SDL_GetKeyName(event.key.keysym.sym));

}

void stringMemory::draw(Graphics &graphicsObj){
    graphicsObj.setRenderDrawColor(255, 255, 255, 255);     // make the screen full white(alpha 255), although white doesn't have alpha
    graphicsObj.drawImage("stringMemBg.png", 0, 0, STRING_MEM_WINDOW_WIDTH, STRING_MEM_WINDOW_HEIGHT);
    
    if(this->_started){
        // custom font for string memory game
        graphicsObj.drawVarText(this->_font, 26, this->_userString, this->_color, 1, 30, 535);
    }
    else{
        this->_startButton->draw(graphicsObj);
    }
}
