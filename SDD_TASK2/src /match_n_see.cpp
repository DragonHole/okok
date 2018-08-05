//
//  match_n_see.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 5/8/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "match_n_see.h"
#include "globals.h"
#include "graphics.h"

match_n_see::match_n_see():_score(0), _steps(0), _quit(false), _save(false){
    initNew();
}

void match_n_see::initNew(){
    for(int i = 0; i < 6; i++)
        this->_pics[i][0] = new Button("cardBack1.png", "cardBack2.png", i*MATCH_N_SEE_PIC_WIDTH, 20, MATCH_N_SEE_PIC_WIDTH, MATCH_N_SEE_PIC_HEIGHT);
    for(int i = 0; i < 6; i++)
        this->_pics[i][1] = new Button("cardBack1.png", "cardBack2.png", i*MATCH_N_SEE_PIC_WIDTH, 165, MATCH_N_SEE_PIC_WIDTH, MATCH_N_SEE_PIC_HEIGHT);
    for(int i = 0; i < 6; i++)
        this->_pics[i][2] = new Button("cardBack1.png", "cardBack2.png", i*MATCH_N_SEE_PIC_WIDTH, 310, MATCH_N_SEE_PIC_WIDTH, MATCH_N_SEE_PIC_HEIGHT);
    for(int i = 0; i < 6; i++)
        this->_pics[i][3] = new Button("cardBack1.png", "cardBack2.png", i*MATCH_N_SEE_PIC_WIDTH, 455, MATCH_N_SEE_PIC_WIDTH, MATCH_N_SEE_PIC_HEIGHT);
    
    this->_exitButton = new Button("stringMemExitButton1.png", "stringMemExitButton2.png", 617, 552, 120, 44);
    this->_saveButton = new Button("stringMemSaveButton1.png", "stringMemSaveButton2.png", 610, 480, 147, 44);
    
    for(int i = 0; i < 6; i++)
        for(int k = 0; k < 4; k++){
            _show[i][k] = false;
        }
    
    this->_type[0][0] = 2;
    this->_type[1][0] = 8;
    this->_type[2][0] = 7;
    this->_type[3][0] = 1;
    this->_type[4][0] = 12;
    this->_type[5][0] = 9;
    this->_type[0][1] = 8;
    this->_type[1][1] = 2;
    this->_type[2][1] = 11;
    this->_type[3][1] = 4;
    this->_type[4][1] = 7;
    this->_type[5][1] = 6;
    this->_type[0][2] = 5;
    this->_type[1][2] = 3;
    this->_type[2][2] = 10;
    this->_type[3][2] = 9;
    this->_type[4][2] = 12;
    this->_type[5][2] = 11;
    this->_type[0][3] = 5;
    this->_type[1][3] = 1;
    this->_type[2][3] = 6;
    this->_type[3][3] = 4;
    this->_type[4][3] = 10;
    this->_type[5][3] = 3;
    
    
    this->_first.first = -1;    // untouched
    this->_second.first = -1;
}

void match_n_see::draw(Graphics &graphicsObj){
    graphicsObj.drawImage("match_n_seeBg.png", 0, 0, MATCH_N_SEE_WINDOW_WIDTH, MATCH_N_SEE_WINDOW_HEIGHT);
    
    for(int i = 0; i < 6; i++)
        for(int k = 0; k < 4; k++){
            if(_show[i][k] == false)
                this->_pics[i][k]->draw(graphicsObj);
            else
                graphicsObj.drawImage(std::to_string(this->_type[i][k]) + ".png", _pics[i][k]->getBoundBox().getX(), _pics[i][k]->getBoundBox().getY(), _pics[i][k]->getBoundBox().getW(), _pics[i][k]->getBoundBox().getH());
        }
    this->_exitButton->draw(graphicsObj);
    this->_saveButton->draw(graphicsObj);
    
    graphicsObj.drawStaticText(32, "tries:", this->_color, 1, 630, 50);
    graphicsObj.drawVarText(33, std::to_string(this->_steps), this->_color, 1, 630, 80);
    graphicsObj.drawVarText(34, "score:", this->_color, 1, 630, 200);
    graphicsObj.drawVarText(35, std::to_string(this->_score), this->_color, 1, 630, 230);
}

Scene match_n_see::update(float elapsedTime){

    bool done  = true;
    for(int i = 0; i < 6; i++)
        for(int k = 0; k < 4; k++)
            if(this->_show[i][k] == false)
                done  = false;
    
    if(this->_quit){
        _quit = false;
        return Scene::MATCH_N_SEE_EXIT;
    }
    
    if(this->_save){
        _save = false;
        return Scene::MATCH_N_SEE_SAVE;
    }
    
    return (done == true) ?Scene::MATCH_N_SEE_DONE:Scene::NONE;
}

void match_n_see::handleButtonEvent(SDL_Event &event){
    this->_exitButton->update(event);
    if(this->_exitButton->isButtonClicked()){
        this->_quit = true;
    }
    
    this->_saveButton->update(event);
    if(this->_saveButton->isButtonClicked()){
        this->_save = true;
    }
    
    for(int i = 0; i < 6; i++)
        for(int k = 0; k < 4; k++){
            this->_pics[i][k]->update(event);
            if(_pics[i][k]->isButtonClicked()){
                if(this->_first.first == -1){
                    _first = std::make_pair(i, k);
                    this->_show[i][k] = true;
                }
                else{
                    this->_second = std::make_pair(i, k);
                    this->_show[i][k] = true;
                    this->_steps++;
                }
            }
        }
    
    if(_first.first != -1 && _second.first != -1){
        if(this->_type[_first.first][_first.second] == this->_type[_second.first][_second.second]){
            // play sound
            this->_score += 50;
            this->_show[_first.first][_first.second] = true;
            this->_show[_second.first][_second.second] = true;
            _first.first = -1;
            _second.first = -1;
            printf("\nmatches");
        }
    
        else{
            this->_show[_first.first][_first.second] = false;
            this->_show[_second.first][_second.second] = false;
            _first.first = -1;
            _second.first = -1;
            printf("\ndoesn't matches");
        }
    }
}

int match_n_see::getScore(){
    return this->_score;
}

void match_n_see::reset(){
    this->_score = 0;
    this->_steps = 0;
    initNew();
}
