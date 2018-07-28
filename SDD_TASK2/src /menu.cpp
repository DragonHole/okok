//
//  menu.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 20/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "menu.h"
#include "graphics.h"
#include "process.h"

Menu::Menu(){
    this->_buttons["tetrisPauseButton"] = new Button("tetrisPauseButton1.png", "tetrisPauseButton2.png", 300, 500, 128, 37);
    
    this->_buttons["tetrisStopMenuResumeButton"] = new Button("tetrisStopMenuResumeButton1.png", "tetrisStopMenuResumeButton2.png", 120, 180, 128, 37);
    
    this->_buttons["tetrisStopMenuRestartButton"] = new Button("tetrisStopMenuRestartButton1.png", "tetrisStopMenuRestartButton2.png", 120, 240, 128, 37);
    
    this->_buttons["tetrisStopMenuMainMenuButton"] = new Button("tetrisStopMenuMainMenuButton1.png", "tetrisStopMenuMainMenuButton2.png", 120, 300, 128, 37);
    
    this->_buttons["tetrisLoseMenuReplayButton"] = new Button("tetrisLoseMenuReplayButton1.png", "tetrisLoseMenuReplayButton2.png", 100, 335, 216, 89);
    
    this->_buttons["mainMenuTetrisButton"] = new Button("mainMenuTetrisButton1.png", "mainMenuTetrisButton2.png", 420, 270, 220, 51);
    
    this->_bgm = Mix_LoadMUS("bgm.mp3");
    this->_buttonClickSound = Mix_LoadWAV("buttonClickSound.wav");
    this->_tetrisBgm = Mix_LoadWAV("tetrisBgm.wav");
    this->_tetrisGameOverSound = Mix_LoadWAV("tetrisGameOverSound.wav");
}

Menu::~Menu(){}

void Menu::drawMainMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("mainMenuBase.png", 0, 0, 736, 552);
    
    this->_buttons["mainMenuTetrisButton"]->draw(graphicsObj);
    
    if(Mix_PlayingMusic() == 0)
        Mix_PlayMusic(this->_bgm, -1);
}

void Menu::drawTetrisDefaultMenu(Graphics& graphicsObj){
    this->_buttons["tetrisPauseButton"]->draw(graphicsObj);
    
    if(Mix_Paused(1) == 1)
        Mix_Resume(1);
    else if(Mix_Playing(1) == 0)
        Mix_PlayChannel(1, _tetrisBgm, -1);
}

void Menu::drawTetrisStopMenu(Graphics &graphicsObj){
    SDL_Color color = {255, 55, 244};
    graphicsObj.drawImage("tetrisStopMenuBase.png", 0, 0, 374, 406);
    
    this->_buttons["tetrisStopMenuResumeButton"]->draw(graphicsObj);
    this->_buttons["tetrisStopMenuRestartButton"]->draw(graphicsObj);
    this->_buttons["tetrisStopMenuMainMenuButton"]->draw(graphicsObj);
}

void Menu::drawTetrisLoseMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("tetrisLoseMenu.png", 0, 0, 796, 482);
    this->_buttons["tetrisLoseMenuReplayButton"]->draw(graphicsObj);
    
    if(Mix_Playing(3) == 0)
        Mix_PlayChannel(3, this->_tetrisGameOverSound, -1);
}

void Menu::handleButtonEvent(SDL_Event &event, Process &process){

    // in this function we handle scene logics
    if(process.getPid() == 1){
        this->_buttons["tetrisPauseButton"]->update(event);
        // if stop button clicked within tetris gaming screen, then trigger process 4
        if(this->_buttons["tetrisPauseButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            process.setPid(4);
            Mix_Pause(1);
        }
    }
    
    if(process.getPid() == 2){
        this->_buttons["tetrisLoseMenuReplayButton"]->update(event);
        if(this->_buttons["tetrisLoseMenuReplayButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            process.setPid(5);
        }
    }
    
    if(process.getPid() == 3){
        this->_buttons["mainMenuTetrisButton"]->update(event);
        if(this->_buttons["mainMenuTetrisButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            Mix_PauseMusic();
            process.setPid(5);
        }
    }
    
    if(process.getPid() == 4){
        this->_buttons["tetrisStopMenuResumeButton"]->update(event);
        if(this->_buttons["tetrisStopMenuResumeButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            process.setPid(1);
        }
        
        this->_buttons["tetrisStopMenuRestartButton"]->update(event);
        if(this->_buttons["tetrisStopMenuRestartButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            process.setPid(5);
        }
        
        this->_buttons["tetrisStopMenuMainMenuButton"]->update(event);
        if(this->_buttons["tetrisStopMenuMainMenuButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            Mix_RewindMusic();
            Mix_PlayMusic(this->_bgm, -1);
            process.setPid(3);
        }
    }

}
