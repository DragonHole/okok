//
//  tetris.h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 26/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef tetris_h
#define tetris_h

// tetris game class

#include "block.h"
#include "SDL2_mixer/SDL_mixer.h"

struct tempRect{
    tempRect(){}
    tempRect(Rect rect, Color color):_rect(rect), _color(color){}
    
    Rect _rect;
    Color _color;
};

class Tetris{
public:
    Tetris();
    
    Tetris(Graphics &graphicsObj);

    ~Tetris();
    
    Scene update(Graphics &graphicsObj, float timeElapsed);
    
    void move(Direction dir);
    
    void rotate();
    
    void draw(Graphics &graphicsObj);
    
    void checkStatus();
    
    void initNewBlock(Graphics &graphicsObj);
    
    void reset(Graphics &graphicsObj);
    
    int getScore();
    int getLevel();
    
private:
    
    std::vector<Rect> _groundedSquares;     // 无奈...
    std::vector<tempRect> _groundedRects;
    Block *_currentBlock;
    int _timeToUpdate;        // used for assigning new blocks
    int _timeElapsed;
    
    int _level;
    int _score;
    int _completedRows;     // internal use
    
    Sprite *_spriteSheets[4];    // four different colors
    Mix_Chunk *_tetrisClearLineSound;
    Mix_Chunk *_tetrisRotateSound;
    Mix_Chunk *_tetrisMoveSound;
};

#endif /* tetris_h */
