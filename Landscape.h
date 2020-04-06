#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GameState.h"
#include "GlobalVars.h"

class Yahdu;

class Landscape : public GameState
{
private:
    // foreground where Yahdu walks
    SDL_Texture * fg;
    // far away background
    SDL_Texture * bg;
    // different depth land tiles
    SDL_Texture * landTiles;
    // // map texture which all tiles are blitted onto
    // SDL_Texture * landmap;

    Yahdu * yahdu;
    
public:

    Landscape(int prevState);
    ~Landscape();
    
    void handleEvents();
    void update();
    void render();

    void generateLand();
};

#endif
