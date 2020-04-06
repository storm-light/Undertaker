#ifndef _YAHDU_H_
#define _YAHDU_H_

#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"
#include "Landscape.h"

class Yahdu
{

private:
    
    int up, down, left, right;
    int dir;
    float buffer;
    
    SDL_Texture * SpriteSheet;
    SDL_Rect hitbox;
    int width, height;
    int SpriteSheetWidth, SpriteSheetHeight;

    int currentFrame;
    int lastFrame;
    
    const static int numFrames = 12;
    SDL_Rect clipsUp[numFrames];
    SDL_Rect clipsDown[numFrames];
    SDL_Rect clipsLeft[numFrames];
    SDL_Rect clipsRight[numFrames];

    int frameUp, frameDown, frameLeft, frameRight;
    
    float x_pos, y_pos;
    float x_vel, y_vel;
    float vel;
    float acc;
    float fric;

    Uint32 lastTime;

    int camX, camY;
    SDL_Rect cam;

public:

    Yahdu();
    ~Yahdu();

    void initAnimation();

    void landSetPos(int x, int y);
    void labSetPos(int x, int y);

    void handleEvents();

    void updateInLand();
    void updateInLab();
    void updateLandCam();
    void updateFrame();

    void renderLandCam();
    void renderLabCam();
    void render(); // cam will become part of Yahdu

    void shiftHitbox();
    bool collisionInLand();
    bool collisionInLab();
    // bool checkTombstoneCollision(Grass grass);

    // bool checkBoneCollision(Grass grass);
};

#endif
