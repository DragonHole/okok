//
//  rect.h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 6/6/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef rect_h
#define rect_h

#include "globals.h"
#include <iostream>

// to do: getcentrex, y getxyhw, gettdlr, getside, checkCollision, chectRectvalid, getrect.

class Rect{
public:
    Rect() {}
    
// Constructor to instantiate a Rect object
    Rect(int x, int y, int width, int height){
        this->_x = x;
        this->_y = y;
        this->_w = width;
        this->_h = height;
    }
    
    const int getX()const{
        return this->_x;
    }
    
    const int getY()const{
        return this->_y;
    }
    
    const int getW()const{
        return this->_w;
    }
    
    const int getH()const{
        return this->_h;
    }
    
    const int getCentreX()const{
        return this->_x + this->_w/2;
    }
    
    const int getCentreY()const{
        return this->_y + this->_h/2;
    }

// Sub-helper functions
// get the x-coordinate for left and right side, y-coordinate for top and bottom sides
    
    const int getTop()const{
        return this->_y;
    }
    
    const int getBottom()const{
        return this->_y + _h;
    }
    
    const int getLeft()const{
        return this->_x;
    }
    
    const int getRight()const{
        return this->_x + _w;
    }
    
// gives the side wanted
    const int getSide(const Side::side side)const{
        return side == Side::side::RIGHT ? this->getRight() :
        Side::side::LEFT ? this->getLeft() :
        Side::side::DOWN ? this->getBottom() :
        Side::side::TOP ? this->getTop() :
        Side::side::NONE;
    }
    
    const Side::side checkCollisionSide(Rect otherRectangle) const{
        int amtRight, amtLeft, amtTop, amtBottom;
        amtRight = this->getRight() - otherRectangle.getLeft();
        amtLeft = otherRectangle.getRight() - getLeft();
        amtTop = otherRectangle.getBottom() - getTop();
        amtBottom = getBottom() - otherRectangle.getTop();
        
        int vals[4] = { abs(amtRight), abs(amtLeft), abs(amtTop), abs(amtBottom) };
        int lowest = vals[0];
        for (int i = 0; i < 4; i++) {
            if (vals[i] < lowest) {
                lowest = vals[i];
            }
        }
        
        return
        // here we return the smallest offset in rects, which is the colliding side
        lowest == abs(amtRight) ? Side::RIGHT :
        lowest == abs(amtLeft) ? Side::LEFT :
        lowest == abs(amtTop) ? Side::TOP :
        lowest == abs(amtBottom) ? Side::DOWN :
        Side::NONE;
    }
    
    // the function to check if two rectangles are colliding in any side, returns true or false
    static const bool checkCollisionWith(const Rect &first, const Rect &second){
        if(first.getTop() <= second.getBottom() &&
           first.getBottom() >= second.getTop() &&
           first.getRight() >= second.getLeft() &&
           first.getLeft() <= second.getRight())
            return true;
        else
            return false;
    }
    
// get the current object
    const inline Rect getRect()const{
        return *this;
    }
    
    void setX(int x){this->_x = x;}
    
    void setY(int y){this->_y = y;}
    

    
private:
    int _x, _y, _w, _h;
    
};
#endif /* rect_h */
