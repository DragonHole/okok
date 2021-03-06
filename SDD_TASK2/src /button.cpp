//
//  button.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 26/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "button.h"
#include "graphics.h"

Button::Button(std::string imageFilePath, std::string imageFilePath2, int x, int y, int w, int h):_imageFilePath(imageFilePath), _imageFilePath2(imageFilePath2), _boundBox(Rect(x, y, w, h)), _isHovered(false), _isClicked(false){}

Button::~Button(){}

void Button::refreshButtonState(){
    this->_isClicked = false;
    this->_isHovered = false;
}

bool Button::isButtonClicked(){
    return this->_isClicked;
}

void Button::update(SDL_Event &event){
    this->_isHovered = false;
    this->_isClicked = false;
    if((Rect::checkCollisionWith(_boundBox, Rect(event.motion.x, event.motion.y, 3, 3)))){
        this->_isHovered= true;
        if(event.type == SDL_MOUSEBUTTONDOWN)
            this->_isClicked = true;
    }
}

void Button::draw(Graphics &graphicsObj){
    if(this->_isHovered){
        graphicsObj.drawImage(this->_imageFilePath2, _boundBox.getX(), _boundBox.getY(), _boundBox.getW(), _boundBox.getH());
        
    }
    else{
        graphicsObj.drawImage(this->_imageFilePath, _boundBox.getX(), _boundBox.getY(), _boundBox.getW(), _boundBox.getH());
    }
}

Rect &Button::getBoundBox(){
    return this->_boundBox;
}
