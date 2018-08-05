//
//  game.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 22/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "game.h"

#define MAX_FRAME_RATE 20

Game::Game():_loaded(false), _loaded2(false){
// init
    loop();
}

Game::~Game(){}

void Game::loop(){
    
    bool quit = false;
    
    // Signed 16-bit samples, in system byte order, hardware specific?
    if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) == -1)
        std::cout<<Mix_GetError()<<std::endl;
    
    this->_menuObj = Menu();
    this->_menuObj.loadUserData();  // calls Login::readUserDetailFromFile
    
    this->_process.setPid(3);
    
    this->_tetrisObj = Tetris(this->_graphicsObj);
    this->_stringMemoryObj = stringMemory();
    this->_match_n_seeObj = match_n_see();

    double LastUpdateTime = SDL_GetTicks();
    
    while(quit == false)
    {
        _keyboardObj.newFrame();
        
        while(SDL_PollEvent(&_event))
        {
    // don't bother with _heldKeys yet
            if(_event.type == SDL_KEYDOWN){
                this->_keyboardObj.keyDown(_event);
                if(this->_process.getPid() == 6 || this->_process.getPid() == 7)
                    this->_menuObj.handleKeyboardEvent(this->_event);
                
                if(this->_process.getPid() == 8)
                    this->_stringMemoryObj.handleKeyboardEvent(this->_event);
            }
            
            if(_event.type == SDL_KEYUP)
                this->_keyboardObj.keyUp(_event);
            
            if(_event.type == SDL_MOUSEMOTION || _event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP){
                this->_menuObj.handleButtonEvent(this->_event, this->_process);
    
                if(this->_process.getPid() == 8)
                    this->_stringMemoryObj.handleButtonEvent(this->_event);
                
                if(this->_process.getPid() == 10)
                    this->_match_n_seeObj.handleButtonEvent(this->_event);
            }
            
    // close the window when the red close button is pressed
            if(_event.type == SDL_QUIT)
                return;
            
    // close the window when key esc is pressed
            if(_event.key.keysym.sym == SDLK_ESCAPE)
                quit=true;
        }
        
        // really it's only handling keyboard input...
        this->handleInput();
        
        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LastUpdateTime;
        
        this->update(ELAPSED_TIME_MS);
        LastUpdateTime = CURRENT_TIME_MS;
        
        this->draw(ELAPSED_TIME_MS);
        
        SDL_Delay(40);  // don't kill the cpu :)
    }
}

void Game::update(double elapsedTime){
    
    switch(this->_process.getPid()){
        case 1:{
            if(this->_tetrisObj.update(this->_graphicsObj, elapsedTime) == Scene::TETRIS_LOSE){
                this->_process.setPid(2);
                
                if(!this->_loaded){
                    this->_menuObj.getScoreFromGame(this->_tetrisObj.getScore());
                    _loaded = true;
                }
            }
            break;
        }
        
        case 8:{
            this->_which = this->_stringMemoryObj.update(this->_graphicsObj, elapsedTime);
            if(_which == Scene::STRINGMEM_EXIT)
                this->_process.setPid(3);
            
            if(_which == Scene::STRINGMEM_SAVE){
                this->_menuObj.getScoreFromGame(this->_stringMemoryObj.getScore());
                this->_menuObj.writeToFile();
            }
            break;
        }
            
        case 10:{
            _which = this->_match_n_seeObj.update(elapsedTime);
            if(_which == Scene::MATCH_N_SEE_DONE)
                this->_process.setPid(9);
            if(_which == Scene::MATCH_N_SEE_SAVE){
                this->_menuObj.getScoreFromGame(this->_match_n_seeObj.getScore());
                this->_menuObj.writeToFile();
            }
            if(_which == Scene::MATCH_N_SEE_EXIT)
                this->_process.setPid(3);
            
            break;
        }
    }
}

// really just keyboard input is processed here
void Game::handleInput(){
    // commands here should be accessible globally
    if(this->_keyboardObj.isKeyPressed(SDL_SCANCODE_Z))
        this->_process.setPid(10);
    
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
            SDL_SetWindowSize(_graphicsObj.getWindow(), TETRIS_LOSE_MENU_WIDTH, TETRIS_LOSE_MENU_HEIGHT);
//            this->_timeElapsed += elapsedTime;
            this->_menuObj.drawTetrisLoseMenu(_graphicsObj);
//
//            // the lose menu remains for 5 seconds
//            if(_timeElapsed > 5000){
//                _timeElapsed -= 5000;
//                this->_process.setPid(1);
//            }
            SDL_Color color = {255, 255, 100};
            this->_graphicsObj.drawVarText(9, std::to_string(this->_tetrisObj.getScore()), color, 2, 258, 75);
            break;
        }
            
        case 3:{
            SDL_SetWindowSize(_graphicsObj.getWindow(), MAIN_MENU_WIDTH, MAIN_MENU_HEIGHT);
            this->_menuObj.drawMainMenu(_graphicsObj);
            break;
        }
            
        case 4:{
            SDL_SetWindowSize(_graphicsObj.getWindow(), TETRIS_STOP_MENU_WIDTH, TETRIS_STOP_MENU_HEIGHT);
            this->_menuObj.drawTetrisStopMenu(this->_graphicsObj);
            break;
        }
            
        case 5:{
            this->_tetrisObj.reset(this->_graphicsObj);
            this->_process.setPid(1);
            break;
        }
            
        case 6:{
            this->_menuObj.drawMainMenuCreateAccountMenu(this->_graphicsObj);
            break;
        }
            
        case 7:{
            this->_menuObj.drawMainMenuLoginMenu(this->_graphicsObj);
            break;
        }
            
        case 8:{
            SDL_SetWindowSize(_graphicsObj.getWindow(), STRING_MEM_WINDOW_WIDTH, STRING_MEM_WINDOW_HEIGHT);
            SDL_SetWindowPosition(_graphicsObj.getWindow(), 200, 180);
            this->_stringMemoryObj.draw(this->_graphicsObj);
            this->_menuObj.drawStringMemDefaultMenu(this->_graphicsObj);
            break;
        }

        case 10:{
            SDL_SetWindowSize(_graphicsObj.getWindow(), MATCH_N_SEE_WINDOW_WIDTH, MATCH_N_SEE_WINDOW_HEIGHT);
            this->_match_n_seeObj.draw(this->_graphicsObj);
            break;
        }
    }

    _graphicsObj.flipRenderer();
}

