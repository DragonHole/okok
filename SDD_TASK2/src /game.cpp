//
//  game.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 22/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "game.h"

#define MAX_FRAME_RATE 20

Game::Game(){
// init
    loop();
}

Game::~Game(){}

void Game::loop(){
    
    SDL_Event event;
    bool quit = false;

    this->_menuObj = Menu();
    this->_process.setPid(1);
    
    //                              smaller the number, faster the block fall|||
    this->_tetrisObj = Tetris(this->_graphicsObj);

    double LastUpdateTime = SDL_GetTicks();
    
    while(quit == false)
    {
        _keyboardObj.newFrame();
        
        while(SDL_PollEvent(&event))
        {
    // don't bother with _heldKeys yet
            if(event.type == SDL_KEYDOWN)
                this->_keyboardObj.keyDown(event);
            
            if(event.type == SDL_KEYUP)
                this->_keyboardObj.keyUp(event);
            
            if(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
                this->_menuObj.handleButtonEvent(event, this->_process);
            
    // close the window when the red close button is pressed
            if(event.type == SDL_QUIT)
                return;
            
    // close the window when key esc is pressed
            if(event.key.keysym.sym == SDLK_ESCAPE)
                quit=true;
        }
        
        printf("\ncurrent pid: %d", _process.getPid());
        
        this->handleInput();
        
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LastUpdateTime;
        
        this->update(ELAPSED_TIME_MS);
        LastUpdateTime = CURRENT_TIME_MS;
        
        this->draw(ELAPSED_TIME_MS);
        
        SDL_Delay(40);  // saves your battery and cpu :)
    }
}

void Game::update(double elapsedTime){
    
    switch(this->_process.getPid()){
        case 1:{
            if(this->_tetrisObj.update(this->_graphicsObj, elapsedTime) == Scene::TETRIS_LOSE)
                this->_process.setPid(2);
            break;
        }
    }
}

void Game::handleInput(){
    // commands here should be accessible globally
    
    if(_keyboardObj.isKeyPressed(SDL_SCANCODE_Z))
        this->_process.setPid(2);
    
    // commands only accessible in specific scene
    switch(this->_process.getPid()){
        case 1:{
            if(this->_keyboardObj.isKeyPressed(SDL_SCANCODE_DOWN))
                this->_tetrisObj.move(DOWN);
    
            if(_keyboardObj.isKeyPressed(SDL_SCANCODE_LEFT))
                this->_tetrisObj.move(LEFT);
    
            if(_keyboardObj.isKeyPressed(SDL_SCANCODE_RIGHT))
                this->_tetrisObj.move(RIGHT);
    
            if(_keyboardObj.isKeyPressed(SDL_SCANCODE_SPACE))
                this->_tetrisObj.rotate();

            break;
        }
    }
}

void Game::draw(double elapsedTime){
    this->_graphicsObj.clearRenderer();
    // used for contolling scenes(screens)
    
    switch(this->_process.getPid()){
        case 1: {
            SDL_SetWindowSize(_graphicsObj.getWindow(), TETRIS_WINDOW_WIDTH, TETRIS_WINDOW_HEGHT);
            
            this->_menuObj.drawTetrisDefaultMenu(this->_graphicsObj);
            this->_tetrisObj.draw(this->_graphicsObj);
            break;}
            
        case 2: {
            this->_timeElapsed += elapsedTime;
            this->_menuObj.drawTetrisLoseMenu(_graphicsObj);
        
            // the lose menu remains for 5 seconds
            if(_timeElapsed > 5000){
                _timeElapsed -= 5000;
                this->_process.setPid(1);
            }
            break;
        }
            
        case 3:{
            break;
        }
            
        case 4:{
            SDL_SetWindowSize(_graphicsObj.getWindow(), TETRIS_STOP_MENU_WIDTH, TETRIS_STOP_MENU_HEIGHT);
            this->_menuObj.drawTetrisStopMenu(_graphicsObj);
            break;
        }
            
        case 5:{
            this->_tetrisObj.reset(this->_graphicsObj);
            this->_process.setPid(1);
            break;
        }
            
    }

    _graphicsObj.flipRenderer();
}

