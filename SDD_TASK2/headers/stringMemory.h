//
//  stringMemory.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 31/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef stringMemory_h
#define stringMemory_h

#include <iostream>
#include "globals.h"

// second unit, prints a string to the screen for few seconds and asks the player to replicate with keyboard

class Graphics;

class stringMemory{
public:
    stringMemory();
    
    stringMemory(Graphics &graphicsObj);
    
    ~stringMemory();
    
    Scene update(Graphics &graphicsObj, double timeElapsed);
    
    void draw(Graphics &graphicsObj);
    
private:
    std::string _currentString;
    
    int _level;
    int _score;
};

#endif /* stringMemory_h */
