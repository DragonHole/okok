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
    this->_buttons["tetrisPauseButton"] = new Button("Stop", "tetrisPauseButton1.png", "tetrisPauseButton2.png", 300, 500, 128, 37);
    
}

Menu::~Menu(){}

void Menu::drawMainMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisDefaultMenu(Graphics& graphicsObj){
    graphicsObj.drawImage("tetrisButtonWrapping.png", 300, 20, 120, 74);
    
    this->_buttons["tetrisPauseButton"]->draw(graphicsObj);
}


void Menu::drawTetrisStopMenu(Graphics &graphicsObj){
    SDL_Color color = {255, 55, 244};
    graphicsObj.drawStaticText(10, "in pause menu", color, 1, 100, 100);
}

void Menu::drawTetrisWinMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisLoseMenu(Graphics &graphicsObj){

}

void Menu::handleButtonEvent(SDL_Event &event, Process &process){

    // in this function we handle scene logics
    if(process.getPid() == 1)
        this->_buttons["tetrisPauseButton"]->update(event);
        // if stop button clicked within tetris gaming screen, then trigger process 4
        if(this->_buttons["tetrisPauseButton"]->isButtonClicked())
            process.setPid(4);

}
