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

Menu::Menu():_clickedOnUsernameOrPassword(0){
    this->_buttons["tetrisPauseButton"] = new Button("tetrisPauseButton1.png", "tetrisPauseButton2.png", 300, 500, 128, 37);
    
    this->_buttons["tetrisStopMenuResumeButton"] = new Button("tetrisStopMenuResumeButton1.png", "tetrisStopMenuResumeButton2.png", 120, 180, 128, 37);
    
    this->_buttons["tetrisStopMenuRestartButton"] = new Button("tetrisStopMenuRestartButton1.png", "tetrisStopMenuRestartButton2.png", 120, 240, 128, 37);
    
    this->_buttons["tetrisStopMenuMainMenuButton"] = new Button("tetrisStopMenuMainMenuButton1.png", "tetrisStopMenuMainMenuButton2.png", 120, 300, 128, 37);
    
    this->_buttons["tetrisLoseMenuReplayButton"] = new Button("tetrisLoseMenuReplayButton1.png", "tetrisLoseMenuReplayButton2.png", 100, 335, 216, 89);
    
    this->_buttons["mainMenuTetrisButton"] = new Button("mainMenuTetrisButton1.png", "mainMenuTetrisButton2.png", 450, 270, 220, 51);
    
    this->_buttons["mainMenuCreateAccountButton"] = new Button("mainMenuCreateAccountButton1.png", "mainMenuCreateAccountButton2.png", 560, 10, 170, 61);
    
    this->_buttons["mainMenuCreateAccountMenuBackButton"] = new Button("mainMenuCreateAccountMenuBackButton1.png", "mainMenuCreateAccountMenuBackButton2.png", 515, 165, 40, 42);
    
    this->_buttons["mainMenuCreateAccountMenuCreateButton"] = new Button("mainMenuCreateAccountMenuCreateButton1.png", "mainMenuCreateAccountMenuCreateButton2.png", 260, 372, 215, 52);
    
    
    
    // since these two are only used for detection, so no image for them. I'm too lazy to write a special method for handling blank space detection... :)呵呵懒鬼
    this->_buttons["mainMenuCreateAccountMenuUsernameLacuna"] = new Button("", "", 325, 231, 194, 25);
    this->_buttons["mainMenuCreateAccountMenuPasswordLacuna"] = new Button("", "", 325, 276, 194, 25);
    
    this->_bgm = Mix_LoadMUS("bgm.mp3");
    this->_buttonClickSound = Mix_LoadWAV("buttonClickSound.wav");
    this->_tetrisBgm = Mix_LoadWAV("tetrisBgm.wav");
    this->_tetrisGameOverSound = Mix_LoadWAV("tetrisGameOverSound.wav");
}

Menu::~Menu(){}

void Menu::drawMainMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("mainMenuBase.png", 0, 0, 736, 552);
    
    this->_buttons["mainMenuTetrisButton"]->draw(graphicsObj);
    this->_buttons["mainMenuCreateAccountButton"]->draw(graphicsObj);
    
    if(Mix_PlayingMusic() == 0)
        Mix_PlayMusic(this->_bgm, -1);
}

void Menu::drawMainMenuCreateAccountMenu(Graphics &graphicsObj){
    graphicsObj.drawImage("mainMenuBase.png", 0, 0, 726, 552);
    graphicsObj.drawImage("MainMenuCreateAccountMenuBase.png", 170, 120, 400, 321);
    
    SDL_Color color = {0, 0, 0};
    if(!this->_loginUserNameTypingStatusLook.empty())
        graphicsObj.drawVarText(9, this->_loginUserNameTypingStatusLook, color, 1, 335, 228);
    
    if(!this->_loginPasswordTypingStatusLook.empty())
        graphicsObj.drawVarText(10, this->_loginPasswordTypingStatusLook, color, 1, 335, 268);
    
    SDL_Color red = {255, 0, 0};
    switch(this->_errorCode){
        case 1:{
            graphicsObj.drawStaticText(11, "couldn't create account, user already existed\n", red, 0.7, 210, 325);
            break; }
        case 2:{
            graphicsObj.drawStaticText(12, "You need a username with SOMETHING in it! jesus christ..", red, 0.7, 210, 325);
            break; }
        case 3:{
            graphicsObj.drawStaticText(13, "\nSeriously? An empty password??!!", red, 0.7, 210, 325);
            break; }
        case 4:{
            graphicsObj.drawStaticText(14, "OK...have a password same as your username seems like a good idea...", red, 0.7, 210, 325);
            break; }
        case 0:{
            graphicsObj.drawStaticText(14, "Account created successfully!", red, 0.7, 210, 325);
            break; }
    }
    
    this->_buttons["mainMenuCreateAccountMenuBackButton"]->draw(graphicsObj);
    this->_buttons["mainMenuCreateAccountMenuCreateButton"]->draw(graphicsObj);
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
    
    if(Mix_Playing(1))
        Mix_Pause(1);
    
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
            Mix_PlayChannel(1, this->_tetrisBgm, -1);
            process.setPid(5);
        }
        
        this->_buttons["mainMenuCreateAccountButton"]->update(event);
        if(this->_buttons["mainMenuCreateAccountButton"]->isButtonClicked()){
           Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            
            // clear the string before another round of input:)
            this->_loginUsernameString.clear();
            this->_loginPasswordString.clear();
            this->_loginUserNameTypingStatusLook.clear();
            this->_loginPasswordTypingStatusLook.clear();
            
            process.setPid(6);
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
            Mix_PlayChannel(1, this->_tetrisBgm, -1);
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
    
    if(process.getPid() == 6){
        this->_buttons["mainMenuCreateAccountMenuBackButton"]->update(event);
        if(this->_buttons["mainMenuCreateAccountMenuBackButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            process.setPid(3);
        }
        
        this->_buttons["mainMenuCreateAccountMenuCreateButton"]->update(event);
        if(this->_buttons["mainMenuCreateAccountMenuCreateButton"]->isButtonClicked()){
            Mix_PlayChannel(-1, this->_buttonClickSound, 0);
            // handle login details
            this->_errorCode = this->_loginObj.addUser(this->_loginUsernameString, this->_loginPasswordString);
            this->_loginObj.writeUserDetailToFile();
        }
        
        this->_buttons["mainMenuCreateAccountMenuUsernameLacuna"]->update(event);
        if(this->_buttons["mainMenuCreateAccountMenuUsernameLacuna"]->isButtonClicked())
            this->_clickedOnUsernameOrPassword = 1;
        
        this->_buttons["mainMenuCreateAccountMenuPasswordLacuna"]->update(event);
        if(this->_buttons["mainMenuCreateAccountMenuPasswordLacuna"]->isButtonClicked())
            this->_clickedOnUsernameOrPassword = 2;
    }
}

void Menu::handleKeyboardEvent(SDL_Event &event, Process &process){
    if(process.getPid() == 6){
        if(this->_clickedOnUsernameOrPassword == 1){
            this->_loginUserNameTypingStatusLook += (SDL_GetKeyName(event.key.keysym.sym));
            this->_loginUsernameString += (SDL_GetKeyName(event.key.keysym.sym));
            if(event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE){
                this->_loginUserNameTypingStatusLook.
                this->_loginUsernameString += (SDL_GetKeyName(event.key.keysym.sym));
            }
        }
         if(this->_clickedOnUsernameOrPassword == 2){
            this->_loginPasswordTypingStatusLook += "*";
            this->_loginPasswordString += (SDL_GetKeyName(event.key.keysym.sym));
        }
    }
}

void Menu::loadUserData(){
    this->_loginObj.readUserDetailFromFile();
}
