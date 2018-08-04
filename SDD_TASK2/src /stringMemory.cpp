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

stringMemory::stringMemory():_currentString(""), _incrementCurrentString(""), _userString(""), _gameOverTrue(false), _started(false), _hint(false), _correct(0), _level(1), _score(0), _elapsedTime(0), _exit(false), _save(false){
    // text color
    this->_color = {0, 0, 0};
    this->_redColor = {255, 0, 0};
    
    this->_startButton = new Button("stringMemStartButton1.png", "stringMemStartButton2.png", 300, 200, 460, 85);
    this->_replayButton = new Button("stringMemReplayButton1.png", "stringMemReplayButton2.png", 470, 55, 113, 45);
    this->_hintButton = new Button("stringMemHintButton1.png", "stringMemHintButton2.png", 320, 53, 142, 49);
    this->_exitButton = new Button("stringMemExitButton1.png", "stringMemExitButton2.png", 0, 1, 120, 44);
    this->_saveButton = new Button("stringMemSaveButton1.png", "stringMemSaveButton2.png", 162, 53, 149, 45);
    
    this->_font = TTF_OpenFont("font2.ttf", 36);
    
    this->_bingoSound = Mix_LoadWAV("stringMemBingoSound.wav");
    this->_wrongSound = Mix_LoadWAV("stringMemWrongSound.wav");
    this->_clickButtonSound = Mix_LoadWAV("buttonClickSound.wav");
}

stringMemory::~stringMemory(){}

Scene stringMemory::update(Graphics &graphicsObj, double timeElapsed){
    // when the strings matche
    if(_started && _correct == 1){
        this->_userString.clear();
    }
    
    // when the strings dont match
    if(_started && _correct == 2){
        this->_userString.clear();
    }
    
    if(this->_exit){
        _exit = false;
        reset();
        return Scene::STRINGMEM_EXIT;
    }
    
    if(this->_save){
        _save = false;
        return Scene::STRINGMEM_SAVE;
    }
    
    return Scene::NONE;
}

void stringMemory::handleButtonEvent(SDL_Event &event){
    this->_exitButton->update(event);
    if(this->_exitButton->isButtonClicked()){
        Mix_PlayChannel(-1, this->_clickButtonSound, 0);
        this->_exit = true;
    }
    
    if(!this->_started && this->_correct == 0){
        this->_startButton->update(event);
        if(this->_startButton->isButtonClicked()){
            Mix_PlayChannel(-1, this->_clickButtonSound, 0);
            this->_started = true;
            genString();
        }
    }
    
    if(this->_started){
        this->_replayButton->update(event);
        if(this->_replayButton->isButtonClicked()){
            Mix_PlayChannel(-1, this->_clickButtonSound, 0);
            printf("replay Button is clicked\n");
            reset();
            genString();
        }
        
        this->_hintButton->update(event);
        if(this->_hintButton->isButtonClicked()){
            // play special track
            this->_userString = _currentString;
            this->_hint = true;
            if(this->_level > 1){
                this->_score -= this->_level *(STRING_MEM_SCORE_PER_LEVEL + STRING_MEM_SCORE_EXTRA_CONSTANT);
                this->_level--;
                this->_currentString.pop_back();
            }
        }
        
        this->_saveButton->update(event);
        if(this->_saveButton->isButtonClicked()){
            Mix_PlayChannel(-1, this->_clickButtonSound, 0);
            this->_save = true;
        }
    }
}

void stringMemory::handleKeyboardEvent(SDL_Event &event){
    // when the strings matche
    if(_started && _correct == 1){
        _correct = 0;
        this->_userString.clear();
    }
    
    // when the strings dont match
    if(_started && _correct == 2){
        _correct = 0;
        this->_userString.clear();
    }

    // if enter is pressed, then check for validity and go on
    if(this->_started && this->_correct == 0)
        if(event.key.keysym.scancode == SDL_SCANCODE_RETURN){
            if(this->_userString == this->_currentString || _hint){
                Mix_PlayChannel(-1, this->_bingoSound, 0);
                _correct = 1;
                std::cout<<"\nstring matches!";
                this->_level++;
                genString();
                this->_score += this->_level *(STRING_MEM_SCORE_PER_LEVEL + STRING_MEM_SCORE_EXTRA_CONSTANT);
            }
            else{
                Mix_PlayChannel(-1, this->_wrongSound, 0);
                _correct = 2;
                std::cout<<"\nstring don't match!";
            }
        }
    
    if(this->_started)                      // human limit:)
        if(strlen(this->_userString.c_str()) < 25 && this->_started)
            this->_userString += (SDL_GetKeyName(event.key.keysym.sym));
    
    if(_hint)
        _hint = false;
}

void stringMemory::draw(Graphics &graphicsObj){
    graphicsObj.setRenderDrawColor(255, 255, 255, 255);     // make the screen full white(alpha 255), although white doesn't have alpha
    graphicsObj.drawImage("stringMemBg.png", 0, 0, STRING_MEM_WINDOW_WIDTH, STRING_MEM_WINDOW_HEIGHT);
    
    if(this->_started){
        // custom font for string memory game
        if(!this->_userString.empty()){
            graphicsObj.drawVarText(this->_font, 26, this->_userString, this->_color, 1, 280, 535);}
        else if(_hint)
            graphicsObj.drawVarText(this->_font, 26, this->_currentString, this->_color, 1, 280, 535);
        else
            graphicsObj.drawVarText(this->_font, 26, " ", this->_color, 1, 280, 535);
        
        graphicsObj.drawVarText(this->_font, 27, this->_incrementCurrentString, this->_color, 1, 510, 260);
        
        // draw current stats
        graphicsObj.drawVarText(this->_font, 28, "Score: " + std::to_string(this->_score), _color, 0.8, 890, 50);
        graphicsObj.drawVarText(this->_font, 29, "Level: " + std::to_string(this->_level), _color, 0.8, 720, 50);
        
        if(this->_correct == 2)
            graphicsObj.drawStaticText(this->_font, 30, "Wrong" , _redColor, 1.001, 460, 449);
        
        this->_replayButton->draw(graphicsObj);
        this->_hintButton->draw(graphicsObj);
        this->_saveButton->draw(graphicsObj);
    }
    else{
        graphicsObj.drawImage("stringMemStartPage.png", 0, 0, STRING_MEM_WINDOW_WIDTH, STRING_MEM_WINDOW_HEIGHT);
        this->_startButton->draw(graphicsObj);
    }
    this->_exitButton->draw(graphicsObj);
}

void stringMemory::genString(){
    this->_incrementCurrentString.clear();
    
    srand((unsigned int)time(NULL));
    for(int i = 0; i < STRING_MEM_INCREMENT_ALPHA_PER_LEVEL; i++){
        // generate random letters and numbers
        this->_incrementCurrentString += this->_alpha[rand()%36];
    }
    
    this->_currentString += this->_incrementCurrentString;
}

void stringMemory::reset(){
    this->_started = false;
    this->_score = 0;
    this->_level = 0;
    this->_correct = 0;
    this->_userString = "";
    this->_currentString = "";
    this->_incrementCurrentString = "";
    this->_statusString = "";
}

int stringMemory::getScore()const{
    return this->_score;
}

