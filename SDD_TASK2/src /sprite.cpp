//
//  sprite.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 5/11/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "graphics.h"
#include "sprite.h"
#include "globals.h"
#include <iostream>

Sprite::Sprite(){}

Sprite::Sprite(Graphics &graphicsObj, const std::string &sourcePath, int sourceX, int sourceY, int width, int height, float targetX, float targetY){
    
    _x = targetX;
    _y = targetY;
    
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;
    
    // we turn the SDL_Surface spritesheet into SDL_Texture here
    this->_textureSheet = SDL_CreateTextureFromSurface(graphicsObj.getRenderer(), graphicsObj.loadImage(sourcePath));
    
    if(_textureSheet == nullptr)
        std::cout<<"\n Sprite::Unable to create Texture:" << sourcePath;
    
//    else
//        std::cout<<"\n Sprite::Created texture: " << sourcePath;

    this->_boundBox = Rect(this->_x, this->_y, _sourceRect.w * Globals::SPRITE_SCALE, _sourceRect.h * Globals::SPRITE_SCALE);
}

Sprite::~Sprite() {}

// draws a clip of an animation
void Sprite::draw(Graphics &graphicsObj, int x, int y){

    SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w *(int)Globals::SPRITE_SCALE, this->_sourceRect.h *(int)Globals::SPRITE_SCALE }; // if you are observative you should've pretty much noticed by now that original sprite sheets have to have the same dimensions as how they were to be displayed on screen. This is imperfect indeed, but i don't need that functionality to set dimensions real-time; since their size don't change. 
    
    // this copies the specific sprite clip into the renderer
    graphicsObj.blitTexture(this->_textureSheet, &this->_sourceRect, &destinationRectangle);
}

// called in each iteration of the game loop, update for collision
void Sprite::update(){
    this->_boundBox = Rect(this->_x, this->_y, this->_sourceRect.w *Globals::SPRITE_SCALE, this->_sourceRect.h *Globals::SPRITE_SCALE);
}

const Rect Sprite::getBoundBox() const{
    return this->_boundBox;
}


//  can actually change the targetX, targetY
void Sprite::setSourceRectX(int value) {
    this->_sourceRect.x = value;
}

void Sprite::setSourceRectY(int value) {
    this->_sourceRect.y = value;
}

void Sprite::setSourceRectW(int value) {
    this->_sourceRect.w = value;
}

void Sprite::setSourceRectH(int value) {
    this->_sourceRect.h = value;
}

