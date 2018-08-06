//
//  match_n_see.h
//  SDD_TASK2
//
//  Created by LIN, Winston on 5/8/18.
//  Copyright © 2018 LIN, Winston. All rights reserved.
//
// third game

#ifndef match_n_see_h
#define match_n_see_h

#include "button.h"
#include "SDL2/SDL.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <map>

class Graphics;

class match_n_see{
public:
    match_n_see();
    
    void initNew();
    
    Scene update(float elapsedTime);
    
    void draw(Graphics &graphicsObj);
    
    void handleButtonEvent(SDL_Event &event);
    
    int getScore();
    
    void reset();
    
private:
    int _score;
    int _steps;
    
    int _rows;
    int _columns;
    
    std::pair<int, int> _first;
    std::pair<int, int> _second;
    
    bool _quit;
    bool _save;
    bool _show[6][4];
    int _type[6][4];    //  12 pairs
    Button *_pics[6][4];
    
    SDL_Color _color = {255, 255, 255};
    
    Button *_exitButton;
    Button *_saveButton;
    Button *_startButton;
    
    Mix_Chunk *_bgMusic;
    Mix_Chunk *_buttonClickSound;
    Mix_Chunk *_flipSound;
    Mix_Chunk *_bingoSound;
    Mix_Chunk *_wrongSound;
};

#endif /* match_n_see_h */
