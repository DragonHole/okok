//
//  menu.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 20/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "menu.h"
#include "graphics.h"

Menu::Menu(){
    this->_buttons.insert(std::pair<int, Rect>(0 ,Rect(100, 100, 100, 48)));
    this->_buttons.insert(std::pair<int, Rect>(1 ,Rect(100, 100, 100, 48)));
    this->_buttons.insert(std::pair<int, Rect>(2 ,Rect(100, 100, 100, 48)));
    this->_buttons.insert(std::pair<int, Rect>(3 ,Rect(100, 100, 100, 48)));
}

Menu::~Menu(){}

void Menu::drawMainMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisMenu(Graphics& graphicsObj){

}

void Menu::drawTetrisWinMenu(Graphics &graphicsObj){
    
}

void Menu::drawTetrisLoseMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("button1.png", this->_buttons.at(1).getX(), this->_buttons.at(1).getY(), this->_buttons.at(1).getW(), this->_buttons.at(1).getH());
}

void Menu::refreshButtonState(){
    this->_isButtonClicked.clear();
}

bool Menu::isButtonClicked(int index)const {
    return (this->_isButtonClicked.count(index));
}

void Menu::checkButtonEvent(SDL_Event &event){
    for(int i = 0; i < this->_buttons.size(); i++){
        if(Rect::checkCollisionWith(this->_buttons[i], Rect(event.motion.x, event.motion.y, 1, 1)))
            this->_isButtonClicked[i] = true;
    }
}
