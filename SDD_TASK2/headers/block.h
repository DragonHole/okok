//
//  block.h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 26/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef block_h
#define block_h

#include "string.h"
#include "rect.h"
#include <vector>
#include "sprite.h"

class Graphics;

class Block : public Sprite{
public:
    Block();
    
// should i add a vector() offset?
    Block(Graphics &graphicsObj, int sourceX, int sourceY, int width, int height, float timeToUpdate, int level, BlockType blockType, Color color, Vector spawnPoint);
    
    ~Block();

    void update(float timeElapsed, std::vector<Rect> allOtherRect);
    
    void draw(Graphics &graphicsObj);
    
    void Move(Direction dir);
    
    void Rotate(std::vector<Rect> otherRect); // no argument needed, rotate in one direction only

// the objOther is the vector of rects confirmed to be colliding with square(s) of the current block
    void handleSideCollison(const Rect &otherRect);
    
    BlockType getBlockType()const;
    
    Color getColorType()const;
    
    bool isGrounded()const;
    
    Rect &getNthSquare(int index);
    
protected:
    float _timeElapsed; // to be inherited by sub-class
    
private:
    void setBlock();
    
    int _x;
    int _y;
    
    int _dy;
    
    bool _grounded;
    Side::side _collidingSide;
    std::vector<Rect> _allOtherSquares;
    int _currentLevel;
    
    Sprite _sprite;
    Color _color;
    BlockType _type;		
    Rect _squares[4];		// could've use sprite, which is much easier, but considering neccisity and performance rect seems like a better choice:)
    float _timeToUpdate;    // used to control the speed at which the block free-falls
};

#endif /* block_h */
