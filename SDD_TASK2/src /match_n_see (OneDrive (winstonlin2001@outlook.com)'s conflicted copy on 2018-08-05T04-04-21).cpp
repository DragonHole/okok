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

match_n_see::match_n_see():_level(1){
    initNew();
}

void match_n_see::initNew(){
    this->_rows = _level + 3;
    this->_columns = _level + 3;
    
    this->_pictures.clear();
    
    int row = 0, col = 0;
    
    for(int i = 0; i < (_columns*_rows); i++){
        int widthEach = MATCH_N_SEE_WINDOW_WIDTH/_columns;
        int heightEach = MATCH_N_SEE_WINDOW_HEIGHT/_rows;
        
        this->_pictures[i] = new picture;
        this->_pictures[i]->_button = new Button("cardBack.png", "cardBack.png", (col)*widthEach, (row)*heightEach, widthEach, heightEach);
        
        row++;
        if(row == _rows){
            row = 0;
            col++;
        }
        this->_pictures[i]->_show = false;
    }
}

void match_n_see::draw(Graphics &graphicsObj){
    for(int i = 0; i < (_columns*_rows); i++){
        if(!this->_pictures.at(i)->_show)
            this->_pictures.at(i)->_button->draw(graphicsObj);
        else{
            // ...
        }
    }
}

Scene match_n_see::update(float elapsedTime){
    
    
    return Scene::NONE;
}

void match_n_see::handleButtonEvent(SDL_Event &event){
    for(int i = 0; i < (_columns*_rows); i++){
        if(this->_pictures.at(i)->_button->isButtonClicked()){
            printf("\n clicked ");
            this->_pictures.at(i)->_show = true;
        }
    }

}
