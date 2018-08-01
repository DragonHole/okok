//
//  Header.h
//  SDD_Minor_project
//
//  Created by LIN, Winston on 21/5/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include "SDL2/SDL.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <map>
#include <string>
#include <vector>

class Rect;
class Sprite;

class Graphics{
    
public:
    Graphics();
    ~Graphics();
    
    // load the SDL_Surface from filePath, and return the address
    SDL_Surface *loadImage(std::string filePath);
    
    // Blit SDL_Texture into this->_renderer
    void blitTexture(SDL_Texture *source, SDL_Rect *srcRect, SDL_Rect *dRect);
    
    // Clear the renderer every time the sprites refresh
    void clearRenderer();
    
    void setRenderDrawColor(int r, int g, int b, int alpha);
    
    // Show the renderer
    void flipRenderer();
    
    // Gives access to this->_renderer
    SDL_Renderer * getRenderer()const;
    
    SDL_Window * getWindow()const;
    
    TTF_Font *getFont()const;

    // draw UI element
    void drawStaticText(int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y);
    void drawVarText(int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y);
    
    // overloaded functions with custom font 
    void drawStaticText(TTF_Font *font, int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y);
    void drawVarText(TTF_Font *font, int identifier, std::string msg, SDL_Color color, double sizeCoef, int x, int y);
    
    void drawImage(std::string identifier, int x, int y, int w, int h);

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    
    TTF_Font *_font;
    
    // use map<> container to store spritesheet surfaces by keys(string)
    std::map<std::string, SDL_Surface*> _spriteSheets;
    
    // 给drawVarLabel()函数用的
    std::map<int, std::string> _labelTextureState;
    std::map<int, SDL_Texture *> _labelTextureContent;

    // for drawImage(), centralized sprite sheet management
    std::map<std::string, Sprite> _imageTextureSheet;
};

#endif /* Header_h */

// text identifier documentation -
// TETRIS
// 1 - "Score"
// 2 - score value
// 3 - "Level"
// 4 - level value
// 5 - "Next Level"
// 6 - next level value
// 7 - "Lines completed"
// 8 - lines completed value
// 9 - Username real-time display in create account page
// 10 - Same as above but for password 
// (11 -> 16) - create account page error message
// 17 -> 22 - login account error message
// 23 - 25 used
// 26 - stringMemoryGameCurrentString 
