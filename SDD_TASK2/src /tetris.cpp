//
//  tetris.cpp
//  SDD_TASK2
//
//  Created by LIN, Winston on 6/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "tetris.h"
#include <iterator>
#include <functional>
#include <algorithm>
#include "graphics.h"

Tetris::Tetris(){}

Tetris::Tetris(Graphics &graphicsObj):
    _currentBlock(nullptr),
    _level(1),
    _score(0),
    _timeToUpdate(3000),
    _timeElapsed(0),
    _completedRows(0)

{
    initNewBlock(graphicsObj);
    
    this->_spriteSheets[0] = new Sprite(graphicsObj, "bluesquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[1] = new Sprite(graphicsObj, "redsquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[2] = new Sprite(graphicsObj, "yellowsquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[3] = new Sprite(graphicsObj, "greensquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
}

Tetris::~Tetris(){
    
}

Scene Tetris::update(Graphics &graphicsObj, float timeElapsed){
    
    this->_currentBlock->update(timeElapsed, this->_groundedSquares);
    
    // handle entity collision before checking grounding
    for(int i = 0; i < this->_groundedRects.size(); i++)
        this->_currentBlock->handleSideCollison(_groundedRects.at(i)._rect);
    
    this->checkStatus();
    
    this->_groundedSquares.clear();
    for(int k = 0; k < _groundedRects.size(); k++)
        this->_groundedSquares.push_back(_groundedRects.at(k)._rect);
    
    this->_timeElapsed += timeElapsed;
    
    // create new block when current block landed the plane 
    if(this->_currentBlock->isGrounded()){
        for(int k = 0; k < 4; k++)
            _groundedRects.push_back(tempRect(_currentBlock->getNthSquare(k), _currentBlock->getColorType()));
        
        delete this->_currentBlock;
        this->_currentBlock = nullptr;
        
        initNewBlock(graphicsObj);
        
// can add this functionality but need to fix, now it makes count in checkStatus() wrong
        
//        if(_timeElapsed > _timeToUpdate){    // control the time interval between current block grounded and new block spawned
//            _timeElapsed -= _timeToUpdate;
//            initNewBlock(graphicsObj);
//        }
    }
    
// shame..
    for(int i = 0; i < _groundedRects.size(); i++)
        if(_groundedRects.at(i)._rect.getBottom() > 504)
            _groundedRects.at(i)._rect.setY(480);
    
    // lastly check if grounded blocks have reached the top
    for(int i = 0; i < this->_groundedRects.size(); i++)
        if(this->_groundedRects[i]._rect.getY() <= 100) //
            return TETRIS_LOSE;   // for lose screen
    
    if(this->_level > 5)
        return TETRIS_WIN;
    
    return NONE;
}

void Tetris::draw(Graphics &graphicsObj){
    
    graphicsObj.drawImage("bg.png", 0, 0, 288, 551);
    
    this->_currentBlock->draw(graphicsObj);
    // todo - change ther followings to graphics.drawImage(...)
    for(int i = 0; i < _groundedRects.size(); i++)
        switch(_groundedRects.at(i)._color){
            case Color::BLUE:
                {this->_spriteSheets[0]->draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::RED:
                {this->_spriteSheets[1]->draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::YELLOW:
                {this->_spriteSheets[2]->draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::GREEN:
                {this->_spriteSheets[3]->draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
        }
    
    SDL_Color color1 = {255, 255, 255};
    graphicsObj.drawStaticText(1, "Score", color1, 1, TETRIS_UI_SCORE_POSITION_X, TETRIS_UI_SCORE_POSITION_Y);
    graphicsObj.drawVarText(2, std::to_string(this->_score),color1, 1, TETRIS_UI_SCORE_POSITION_X, TETRIS_UI_SCORE_POSITION_Y + 30);
    
    graphicsObj.drawStaticText(3, "Level", color1, 1, TETRIS_UI_LEVEL_POSITION_X, TETRIS_UI_LEVEL_POSITION_Y);
    graphicsObj.drawVarText(4, std::to_string(this->_level), color1, 1, TETRIS_UI_LEVEL_POSITION_X, TETRIS_UI_LEVEL_POSITION_Y + 30);
    
    graphicsObj.drawStaticText(5, "Next Level", color1, 0.5, TETRIS_UI_SCORE_PER_LEVEL_X, TETRIS_UI_SCORE_PER_LEVEL_Y);
    graphicsObj.drawVarText(6, std::to_string(this->_level * TETRIS_SCORE_NEEDED_PER_LEVEL), color1, 0.5, TETRIS_UI_LEVEL_POSITION_X, TETRIS_UI_SCORE_PER_LEVEL_Y + 30);
    
    // todo- draw "block next" 
}

void Tetris::move(Direction dir){
    this->_currentBlock->Move(dir);
}

void Tetris::rotate(){
    this->_currentBlock->Rotate(this->_groundedSquares); // need to change later
}

void Tetris::initNewBlock(Graphics &graphicsObj){
    srand(SDL_GetTicks());  // use game-time as seed to randomize at each call
    
    // implicit static cast from enumeration to numeraic value here, remember this has no validation on exceptions like index out of range or explicit values given to the enums, ANY exception WILL cause error.
    Color color = Color(rand() % 4);
    BlockType blockType = BlockType(rand() % 7);
    
    this->_currentBlock = new Block(graphicsObj, 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, (TETRIS_MS_TO_UPDATE - _level * TETRIS_MS_TO_UPDATE_DIFFERENCE), _level, blockType, color, Vector(120, 24));
}

void Tetris::checkStatus(){
    
    // iterate level
    if(this->_score >= TETRIS_SCORE_NEEDED_PER_LEVEL * this->_level){
        this->_level++;
    }
    
    // check if line could be cleared
    int count[20] = {0};
    
    for(int i = 0; i < _groundedRects.size(); i++){
        count[(_groundedRects.at(i)._rect.getY() - 24)/24]++;
    }
    
    for (int line = 0; line <21; ++line)
        if (count[line] == 10){
            _completedRows++;
            _score += TETRIS_SCORE_PER_LINE;
            
            for (int i=0; i<_groundedRects.size(); ++i)
                if ((((_groundedRects[i]._rect.getY()) - 24) / TETRIS_SQUARE_HEIGHT) == line){
                    _groundedRects.erase(_groundedRects.begin() + i);
                    i--;
                }
        }
    
    for (int i = 0; i < _groundedRects.size(); ++i)
        for (int line = 0; line < 21; ++line)
        {
            if (count[line] == 10)
            {
                int row = (_groundedRects[i]._rect.getY() - 24) / TETRIS_SQUARE_HEIGHT;
                if (line > row)
                    _groundedRects[i]._rect.setY(_groundedRects[i]._rect.getY() + TETRIS_SQUARE_HEIGHT);
            }
        }
}

void Tetris::reset(){
    // this destroys all the objects but doesn't deallocate memory, only clears index
    this->_groundedSquares.clear();
    this->_groundedRects.clear();
    
    // ISO c11's shrink_to_fit() is more idiomatic but doesn't guarantee complete deallocation
    // so i've used a trick here. with the statement below i've created a rvalue of an empty vector. And since the scope of a rvalue is restricted to the current statement, right after the statement it reached its scope and default destructor gets called, associated data freed by system. A good lesson learnt here :)
    std::vector<Rect>().swap(this->_groundedSquares);
    std::vector<tempRect>().swap(this->_groundedRects);
    
    delete this->_currentBlock;
    this->_currentBlock = nullptr;
    
    this->_timeElapsed = 0;
    
    this->_level = 1;
    this->_score = 0;
    this->_completedRows = 0;     // internal use
}

