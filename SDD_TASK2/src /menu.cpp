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
    
    this->_buttons["tetrisStopMenuResumeButton"] = new Button("tetrisStopMenuResumeButton1.png", "tetrisStopMenuResumeButton2.png", 120, 200, 128, 37);
    
    this->_buttons["tetrisStopMenuRestartButton"] = new Button("tetrisStopMenuRestartButton1.png", "tetrisStopMenuRestartButton2.png", 120, 154, 128, 37);
    
    this->_buttons["tetrisLoseMenuReplayButton"] = new Button("tetrisLoseMenuReplayButton.png", "tetrisLoseMenuReplayButton.png", 100, 335, 216, 89);
}

Menu::~Menu(){}

void Menu::drawMainMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisDefaultMenu(Graphics& graphicsObj){
    this->_buttons["tetrisPauseButton"]->draw(graphicsObj);
}


void Menu::drawTetrisStopMenu(Graphics &graphicsObj){
    SDL_Color color = {255, 55, 244};
    graphicsObj.drawImage("tetrisStopMenuBase.png", 0, 0, 374, 406);
    
    this->_buttons["tetrisStopMenuResumeButton"]->draw(graphicsObj);
    this->_buttons["tetrisStopMenuRestartButton"]->draw(graphicsObj);
}

void Menu::drawTetrisWinMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisLoseMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("tetrisLoseMenu.png", 0, 0, 796, 482);
    
    this->_buttons["tetrisLoseMenuReplayButton"]->draw(graphicsObj);
}

void Menu::handleButtonEvent(SDL_Event &event, Process &process){

    // in this function we handle scene logics
    if(process.getPid() == 1){
        this->_buttons["tetrisPauseButton"]->update(event);
        // if stop button clicked within tetris gaming screen, then trigger process 4
        if(this->_buttons["tetrisPauseButton"]->isButtonClicked())
            process.setPid(4);
    }
    
    if(process.getPid() == 2){
        this->_buttons["tetrisLoseMenuReplayButton"]->update(event);
        if(this->_buttons["tetrisLoseMenuReplayButton"]->isButtonClicked())
            process.setPid(5);
    }
    
    if(process.getPid() == 4){
        this->_buttons["tetrisStopMenuResumeButton"]->update(event);
        if(this->_buttons["tetrisStopMenuResumeButton"]->isButtonClicked())
            process.setPid(1);
        
        this->_buttons["tetrisStopMenuRestartButton"]->update(event);
        if(this->_buttons["tetrisStopMenuRestartButton"]->isButtonClicked())
            process.setPid(5);
    }

}
