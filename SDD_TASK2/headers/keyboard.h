//
//  keyboard .h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 25/5/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef keyboard__h
#define keyboard__h

#include "SDL2/SDL.h"
#include <map>

class Keyboard{
public:
    
    // record current keyboard status from *event
    void keyUp(SDL_Event &event);
    void keyDown(SDL_Event &event);

    // result for key status querie
    bool isKeyPressed(SDL_Scancode k);
    bool isKeyHeld(SDL_Scancode k);
    bool isKeyNull(SDL_Scancode k);
    
    // clear all the key status for next frame iteration
    void newFrame();
    
private:
    // map<> to store the keyboard status in this frame
    std::map<SDL_Scancode, bool> _pressedKey;
    std::map<SDL_Scancode, bool> _heldKey;
    std::map<SDL_Scancode, bool> _nullKey;
};

#endif /* keyboard__h */
