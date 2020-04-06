#ifndef _LAB_H_
#define _LAB_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GameState.h"

class Lab : public GameState
{
private:

    SDL_Texture * bg;

    int baselvl;

    Yahdu * yahdu;
    
public:

    Lab();
    ~Lab();
    
    void handleEvents();
    void update();
    void render();
    
};

#endif
