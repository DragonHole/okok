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

Tetris::Tetris(){}

Tetris::Tetris(Graphics &graphicsObj): _currentBlock(nullptr), _level(1), _score(0){
    initNewBlock(graphicsObj);
    
    this->_spriteSheets[0] = Sprite(graphicsObj, "bluesquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[1] = Sprite(graphicsObj, "redsquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[2] = Sprite(graphicsObj, "yellowsquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
    this->_spriteSheets[3] = Sprite(graphicsObj, "greensquare.png", 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, 0, 0);
}

Tetris::~Tetris(){
    
}

void Tetris::update(Graphics &graphicsObj, float elapsedTime){
    this->_currentBlock->update(elapsedTime, this->_groundedSquares);
    
    this->checkStatus();
    
    this->_groundedSquares.clear();
    for(int k = 0; k < _groundedRects.size(); k++)
        this->_groundedSquares.push_back(_groundedRects.at(k)._rect);
    
    // handle entity collision before checking grounding
    for(int i = 0; i < this->_groundedRects.size(); i++)
        this->_currentBlock->handleSideCollison(_groundedRects.at(i)._rect);
    
    if(this->_currentBlock->isGrounded()){
        for(int k = 0; k < 4; k++)
            _groundedRects.push_back(tempRect(_currentBlock->getNthSquare(k), _currentBlock->getColorType()));
        
        initNewBlock(graphicsObj);
    }
}

void Tetris::draw(Graphics &graphicsObj){
    this->_currentBlock->draw(graphicsObj);
    
    for(int i = 0; i < _groundedRects.size(); i++)
        switch(_groundedRects.at(i)._color){
            case Color::BLUE:
                {this->_spriteSheets[0].draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::RED:
                {this->_spriteSheets[1].draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::YELLOW:
                {this->_spriteSheets[2].draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
            case Color::GREEN:
                {this->_spriteSheets[3].draw(graphicsObj, _groundedRects.at(i)._rect.getX(), _groundedRects.at(i)._rect.getY()); break;}
        }
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
    
    this->_currentBlock = new Block(graphicsObj, 0, 0, TETRIS_SQUARE_WIDTH, TETRIS_SQUARE_HEIGHT, TETRIS_MS_TO_UPDATE, _level, blockType, color, Vector(120, 24));
}

void Tetris::checkStatus(){
    // check if line could be cleared
    int count[20] = {0};
    
    for(int i = 0; i < _groundedRects.size(); i++){
        count[(_groundedRects.at(i)._rect.getY() - 24)/24]++;
    }
    
    printf("\n%d", count[19]);
    
    for (int line=0; line<21; ++line)
    {
        if (count[line] == 4)
        {
//            completeRows++;
            for (int i=0; i<_groundedRects.size(); ++i)
            {
                if (((_groundedRects[i]._rect.getY()) / 24) == line - 24)
                {
//                    delete _groundedRects[i];
                    _groundedRects.erase(_groundedRects.begin() + i);
                    i--;
                }
            }
        }
    }
}


