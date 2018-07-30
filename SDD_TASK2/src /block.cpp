//
//  block.cpp
//  SDD_Minor_project
//
//  Created by LIN, Winston on 26/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#include "block.h"

// each block 

Block::Block() {}

Block::Block(Graphics &graphicsObj, int sourceX, int sourceY, int width, int height, float timeToupdate, int level, BlockType blockType, Color color, Vector spawnPoint):
        _x(spawnPoint._x),
        _y(spawnPoint._y + 24),
        _type(blockType),
        _color(color),
        _grounded(false),
        _collidingSide(Side::NONE),
        _currentLevel(level),
        _timeToUpdate(timeToupdate),
        _dy(TETRIS_INITIAL_FALLING_SPEED),
        _timeElapsed(0)
{
    std::string tempPath = (this->_color == Color::BLUE) ? "bluesquare.png" :
                           (this->_color == Color::GREEN) ? "greensquare.png" :
                           (this->_color == Color::RED) ? "redsquare.png" :
                           "yellowsquare.png"; // otherwise yellow
    
    this->_sprite = Sprite(graphicsObj, tempPath, sourceX, sourceY, width, height, spawnPoint._x, spawnPoint._y);
    
    for(int i = 0; i < 4; ++i)
        this->_squares[i] = Rect();
    
    setBlock();
}

Block::~Block(){}

void Block::draw(Graphics &graphics){
    for(int i = 0; i < 4; ++i){
        this->_sprite.draw(graphics, this->_squares[i].getX(), this->_squares[i].getY());
    }
}

void Block::update(float timeElapsed, std::vector<Rect> allOtherSquares){
    this->_timeElapsed += timeElapsed;
    
    this->_allOtherSquares.clear();
    for(int i = 0; i < allOtherSquares.size(); i++)
        this->_allOtherSquares.push_back(allOtherSquares.at(i));
       
// not allowing movement after landing
 if(_grounded != true)
    if(_timeElapsed > _timeToUpdate){
        _timeElapsed -= _timeToUpdate;
        for(int i = 0; i < 4; ++i)
            this->_squares[i].setY(_squares[i].getY() + TETRIS_INITIAL_FALLING_SPEED + _currentLevel * TETRIS_SPEED_CHANGE);
    }
// check if landed
    if(!_grounded)
    for(int i = 0; i < 4; ++i)
        if(this->_squares[i].getY() >= (TETRIS_GAME_AREA_HEIGHT - 46 - TETRIS_SQUARE_HEIGHT))
            this->_grounded = true;
}

// a lot of hard code here...but it's reasonable.
void Block::setBlock(){
    
    switch(this->_type){
        case SQUARE_BLOCK:{
            this->_squares[0] = Rect(_x, _y, 24, 24);
            this->_squares[1] = Rect(_x + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[2] = Rect(_x, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break; }
          
        case T_BLOCK:{
            this->_squares[0] = Rect(_x + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[1] = Rect(_x, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[2] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break;
        }
        
        case S_BLOCK:{
            this->_squares[0] = Rect(_x + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[1] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[2] = Rect(_x , _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break;
        }
            
        case LONG_BLOCK:{
            this->_squares[0] = Rect(_x + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[1] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[2] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            break;
        }
            
        case BACKWARDS_S_BLOCK:{
            this->_squares[0] = Rect(_x, _y, 24, 24);
            this->_squares[1] = Rect(_x + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[2] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break;
        }
            
        case L_BLOCK:{
            this->_squares[0] = Rect(_x, _y, 24, 24);
            this->_squares[1] = Rect(_x, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[2] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break;
        }
            
        case BACKWARDS_L_BLOCK:{
            this->_squares[0] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y, 24, 24);
            this->_squares[1] = Rect(_x, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[2] = Rect(_x + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            this->_squares[3] = Rect(_x + TETRIS_SQUARE_WIDTH + TETRIS_SQUARE_WIDTH, _y + TETRIS_SQUARE_HEIGHT, 24, 24);
            break;
        }
    }
}

// make canMove a common flag across sections?
void Block::Move(Direction dir){
    bool canMove = true;
    bool squareUnderNeath = false;
    int moveDownSpace = 0;
    
    if(this->_grounded != true)
        switch(dir){
            case DOWN:{
                moveDownSpace = std::max(std::max(_squares[0].getY(), _squares[1].getY()), std::max(_squares[2].getY(), _squares[3].getY()));
                
                for(int i = 0; i < 4; ++i){
                    if((_squares[i].getY() + 2*TETRIS_SQUARE_WIDTH) > (TETRIS_GAME_AREA_HEIGHT - 46)) //special offset
                        canMove = false;
                    for(int k = 0; k < _allOtherSquares.size(); k++)
                        if(((_squares[i].getBottom() + TETRIS_SQUARE_HEIGHT) > _allOtherSquares.at(k).getTop()) && _squares[i].getX() == _allOtherSquares.at(k).getX()){ //check x pos
                            squareUnderNeath = true;
                        }
                }
    
                if((canMove) && (!squareUnderNeath))
                    for(int i = 0; i < 4; ++i)
                        this->_squares[i].setY(_squares[i].getY() + TETRIS_SQUARE_WIDTH);
                
                else if((!canMove) && (!squareUnderNeath))
                    for(int k = 0; k < 4; ++k)
                        this->_squares[k].setY(_squares[k].getY() + (480 - moveDownSpace));
                
                else if((canMove) && (squareUnderNeath))
                    for(int i = 0; i < 4; ++i)
                        this->_squares[i].setY(_squares[i].getY() + TETRIS_INITIAL_FALLING_SPEED + this->_currentLevel*TETRIS_SPEED_CHANGE);
                break; }
                
            case LEFT:{
                for(int i = 0; i < 4; ++i)
                    if(((_squares[i].getX() - TETRIS_SQUARE_WIDTH) < TETRIS_SQUARE_WIDTH) || this->_collidingSide == Side::LEFT)
                        canMove = false;
                if(canMove)
                    for(int i = 0; i < 4; ++i)
                        this->_squares[i].setX(_squares[i].getX() - TETRIS_SQUARE_WIDTH);
                break; }
                
            case RIGHT:{
                for(int i = 0; i < 4; ++i)
                    if(((_squares[i].getX() + 2*TETRIS_SQUARE_WIDTH) > (TETRIS_GAME_AREA_WIDTH - TETRIS_SQUARE_WIDTH)) || this->_collidingSide == Side::RIGHT) // 2*width because x at the left side
                        canMove = false;
                if(canMove)
                    for(int i = 0; i < 4; ++i)
                        this->_squares[i].setX(_squares[i].getX() + TETRIS_SQUARE_WIDTH);
                break; }
            }
    this->_collidingSide = Side::NONE;
}


void Block::Rotate(std::vector<Rect> otherRect){
    if(!this->_grounded){
        int x1 = (_squares[0].getY()-_squares[1].getY()) + _squares[1].getX();
        int y1 = (_squares[1].getX()-_squares[0].getX()) + _squares[1].getY();
        
        int x3 = (_squares[2].getY()-_squares[1].getY()) + _squares[1].getX();
        int y3 = (_squares[1].getX()-_squares[2].getX()) + _squares[1].getY();
        
        int x4 = (_squares[3].getY()-_squares[1].getY()) + _squares[1].getX();
        int y4 = (_squares[1].getX()-_squares[3].getX()) + _squares[1].getY();
        
        bool canMove = false;
    // todo: left side collision and top collision(or leave it)? // update:added and fixed
        if(((x1 + TETRIS_SQUARE_WIDTH) < TETRIS_GAME_AREA_WIDTH) && ((x3 + TETRIS_SQUARE_WIDTH) < TETRIS_GAME_AREA_WIDTH) && ((x4 + TETRIS_SQUARE_WIDTH) < TETRIS_GAME_AREA_WIDTH) && ((y1 + 2*TETRIS_SQUARE_HEIGHT) < TETRIS_GAME_AREA_HEIGHT) && ((y3 + 2*TETRIS_SQUARE_HEIGHT) < TETRIS_GAME_AREA_HEIGHT) && ((y4 + 2*TETRIS_SQUARE_HEIGHT) < TETRIS_GAME_AREA_HEIGHT) && ((x1) > 0) && ((x3) > 0) && ((x4) > 0)) // 最后这三个就是我后来加的
                canMove = true;
        
        for(int i = 0; (i-1) < otherRect.size(); i++)
            if(Rect::checkCollisionWith(otherRect.at(i), Rect(x1, y1, 24, 24)) || Rect::checkCollisionWith(otherRect.at(i), Rect(x3, y3, 24, 24)) || Rect::checkCollisionWith(otherRect.at(i), Rect(x4, y4, 24, 24)))
                canMove = false;
        
        if(canMove){
            _squares[0].setX(x1);
            _squares[2].setX(x3);
            _squares[3].setX(x4);
        
            _squares[0].setY(y1);
            _squares[2].setY(y3);
            _squares[3].setY(y4);
        }
    }
}

void Block::handleSideCollison(const Rect &otherRect){
    if(!_grounded){
        for(int k = 0; k < 4; ++k){
            // handles(by setting flag) when current rect's downside is touching others
            if((this->_squares[k].getX() == otherRect.getX()) && (this->_squares[k].getBottom() == otherRect.getTop()))
                _grounded = true;
            
            // handles when current rect's left side is touching others
            else if (((this->_squares[k].getBottom() < otherRect.getBottom() && this->_squares[k].getBottom() > otherRect.getTop()) || ((this->_squares[k].getTop() < otherRect.getBottom() && this->_squares[k].getTop() > otherRect.getTop())) || this->_squares[k].getTop() == otherRect.getTop()) && (this->_squares[k].getLeft() == otherRect.getRight()))
                _collidingSide = Side::LEFT;
            
            // handles when current rect's right side is touching others
            else if (((this->_squares[k].getBottom() < otherRect.getBottom() && this->_squares[k].getBottom() > otherRect.getTop()) || ((this->_squares[k].getTop() < otherRect.getBottom() && this->_squares[k].getTop() > otherRect.getTop())) || this->_squares[k].getTop() == otherRect.getTop()) && (this->_squares[k].getRight() == otherRect.getLeft()))
                    _collidingSide = Side::RIGHT;
        }
    }
}

BlockType Block::getBlockType()const {
    return this->_type;
}

Rect &Block::getNthSquare(int index){
    return this->_squares[index];
}

bool Block::isGrounded()const {
    return this->_grounded;
}

Color Block::getColorType()const{
    return this->_color;
}
