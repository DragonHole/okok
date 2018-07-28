//
//  graphics.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 21/5/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include <iostream>
#include "SDL2_image/SDL_image.h"
#include "graphics.h"
#include "globals.h"
#include "rect.h"
#include "Sprite.h"

Graphics::Graphics(){
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    
    //Create an application window with the following settings:
    _window = SDL_CreateWindow("Tetris",                     // window title
                              SDL_WINDOWPOS_UNDEFINED,           // initial x position
                              SDL_WINDOWPOS_UNDEFINED,           // initial y position
                              TETRIS_WINDOW_WIDTH,                               // width, in pixels
                              TETRIS_WINDOW_HEGHT,                               // height, in pixels
                              SDL_WINDOW_SHOWN// flags
                              );
    
    _renderer= SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(_renderer);
    
    this->_font = TTF_OpenFont("font.ttf", 26);
    if(!_font)
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    
    TTF_SetFontStyle(_font, TTF_STYLE_BOLD);
}

Graphics::~Graphics(){
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    
    TTF_CloseFont(_font);
    
    TTF_Quit();
    SDL_Quit();
}

// load the spritesheet if not already loaded into the map
SDL_Surface *Graphics::loadImage(std::string filePath){
    if(this->_spriteSheets.count(filePath) == 0)
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    return this->_spriteSheets[filePath];
}

void Graphics::blitTexture(SDL_Texture *source, SDL_Rect *srcRect, SDL_Rect *dRect){
    SDL_RenderCopy(this->_renderer, source, srcRect, dRect);
}

void Graphics::clearRenderer(){
    SDL_RenderClear(this->_renderer);
}

void Graphics::flipRenderer(){
    SDL_RenderPresent(this->_renderer);
}
SDL_Renderer* Graphics::getRenderer()const{
    return this->_renderer;
}

TTF_Font *Graphics::getFont()const{
    return this->_font;
}

void Graphics::drawVarText(int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y){
    if(this->_labelTextureState[identifier] != msg || !this->_labelTextureState.count(identifier)){
        SDL_Surface* surface = TTF_RenderText_Blended(this->_font, msg.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
        
        this->_labelTextureContent[identifier] = texture;
        this->_labelTextureState[identifier] = msg;
 // no need to query texture in this particular scenario, since we still have this surface alive.
        SDL_Rect rect = {
            x, y, surface->w, surface->h
        };
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
    }
// this code is a bit ugly but... doesn't matter
    else if (this->_labelTextureState[identifier] == msg){
        int width = 0, height = 0;
        SDL_QueryTexture(this->_labelTextureContent[identifier], NULL, NULL, &width, &height);
        SDL_Rect rect = {
            x, y, static_cast<int>(width * sizeCoef), static_cast<int>(height * sizeCoef)
        };
        SDL_RenderCopy(_renderer, this->_labelTextureContent[identifier], NULL, &rect);
    }
}

void Graphics::drawStaticText(int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y){
    if(this->_labelTextureContent.count(identifier) == 0){
        SDL_Surface *surface = TTF_RenderText_Solid(this->_font, msg.c_str(), color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
        this->_labelTextureContent[identifier] = texture;
        SDL_FreeSurface(surface);
    }
    
    else{
        int width = 0, height = 0;
        SDL_QueryTexture(this->_labelTextureContent[identifier], NULL, NULL, &width, &height);
        SDL_Rect rect = {
            x, y, static_cast<int>(width * sizeCoef), static_cast<int>(height * sizeCoef)
        };
        SDL_RenderCopy(_renderer, this->_labelTextureContent[identifier], NULL, &rect);
    }
}

void Graphics::drawImage(std::string identifier, int x, int y, int w, int h){
    if(this->_imageTextureSheet.count(identifier) == 0)
        _imageTextureSheet[identifier] = Sprite(*this, identifier, 0, 0, w, h, x, y);
    else
        _imageTextureSheet[identifier].draw(*this, x, y);
}

SDL_Window *Graphics::getWindow()const{
    return this->_window;
}


