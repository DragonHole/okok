//
//  keyboard.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 25/5/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "keyboard.h"

void Keyboard::keyDown(SDL_Event &event){
    this->_pressedKey[event.key.keysym.scancode] = true;
}


void Keyboard::keyUp(SDL_Event &event){
    this->_nullKey[event.key.keysym.scancode] = true;
}

bool Keyboard::isKeyPressed(SDL_Scancode k){
    return this->_pressedKey[k];
}

bool Keyboard::isKeyHeld(SDL_Scancode k){
    return this->_heldKey[k];
}

bool Keyboard::isKeyNull(SDL_Scancode k){
    return this->_nullKey[k];
}

void Keyboard::newFrame(){
    this->_pressedKey.clear();
    this->_heldKey.clear();
}
