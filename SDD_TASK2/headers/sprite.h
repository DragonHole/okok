//
//  sprite.hpp .h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 31/5/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef sprite_hpp__h
#define sprite_hpp__h

#include "SDL2/SDL.h"
#include "rect.h"
#include <string>

// forward declare Graphics class,
class Graphics;

// this class is responsible for all the visual objects in the program
class Sprite{
    
public:
    Sprite();
    
    // acquire all the info to create a sprite object
    Sprite(Graphics &graphicsObj, const std::string &filePath, int sourceX, int sourceY, int width, int height, float targetX, float targetY);
    
    // class destructor should be virtual because this class contains virtual member functions(C++ convention) LOL
    virtual ~Sprite();
    
    // update() will also be virtual for the same reason
    virtual void update();

    void draw(Graphics &graphics, int x, int y);
    
    const Rect getBoundBox() const;
//    const Side::side checkCollisionBoxSide(Rect otherRectangle) const;
    
    // getter functions
    const inline float getX()const {return this->_x;}
    const inline float getY()const {return this->_y;}
    
    void setSourceRectX(int value);
    void setSourceRectY(int value);
    void setSourceRectW(int value);
    void setSourceRectH(int value);
    
protected:
    float _x, _y;
    
    Rect _boundBox;
    
    SDL_Rect _sourceRect;

    SDL_Texture *_textureSheet;
    
private:
    
    
};


#endif /* sprite_hpp__h */
