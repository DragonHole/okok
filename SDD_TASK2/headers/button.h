//
//  button.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 26/7/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef button_h
#define button_h

#include "rect.h"
#include <string>
#include "sprite.h"

class Button{
public:
    Button();
    Button(std::string label, std::string imageFilePath, std::string imageFilePath2, int x, int y, int w, int h);
    
    ~Button();
    
    // clear this->_isClicked and isHovered at each new iteration of the game loop
    void refreshButtonState();

    // interface function: return true if a certain is pressed
    bool isButtonClicked()const;
    
    void update(SDL_Event &event);
    
    void draw(Graphics &graphicsObj);

private:
    Rect _boundBox;

    // to add some graphics effect to the button's look
    bool _isHovered;
    bool _isClicked;
    
    std::string _imageFilePath;     // unclicked button
    std::string _imageFilePath2;    // clicked button
    std::string _label;             // text displayed on the button
};

#endif /* button_h */
