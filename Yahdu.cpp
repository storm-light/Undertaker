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
#include "Yahdu.h"
// fix multiple include header file problem (avoid duplication)

Yahdu::Yahdu()
{
    // variables controlled by input
    up = 0;
    down = 0;
    left = 0;
    right = 0;                  // noooe
    dir = rightDir + 2;

    // sprite sheet loaded for Yahdu
    SpriteSheet = loadTexture(rend, "Turtur.png");
    
    // W/H for rendered Yahdu vs. SpriteSheet lengths
    width = 32; height = 32;
    SpriteSheetWidth = 16; SpriteSheetHeight = 16;

    // frames of animation for diff dir of animation
    frameUp = 0; frameDown = 0; frameLeft = 0; frameRight = 0;

    x_pos = 0;
    y_pos = 0;
    x_vel = 0;
    y_vel = 0;
    vel = 120;                 // default is 120
    acc = 5;                   // default is 5
    fric = 3;

    lastTime = 0;

    camX = 0; camY = 0;
    cam.w = winW; cam.h = winH;

    initAnimation();
}

Yahdu::~Yahdu()
{
    SDL_DestroyTexture(SpriteSheet);
}

void Yahdu::initAnimation()
{
    // animation initialization
    SDL_Rect r;
    r.w = SpriteSheetWidth; r.h = SpriteSheetHeight;

    // leftward animation for sprite
    r.x = 0; r.y = 0; 
    clipsLeft[0] = r;
    r.x = SpriteSheetWidth * 1; r.y = SpriteSheetHeight * 0; 
    clipsLeft[1] = r;
    r.x = SpriteSheetWidth * 2; r.y = SpriteSheetHeight * 0; 
    clipsLeft[2] = r;
    r.x = SpriteSheetWidth * 3; r.y = SpriteSheetHeight * 0; 
    clipsLeft[3] = r;
    r.x = SpriteSheetWidth * 4; r.y = SpriteSheetHeight * 0; 
    clipsLeft[4] = r;
    r.x = SpriteSheetWidth * 5; r.y = SpriteSheetHeight * 0; 
    clipsLeft[5] = r;
    r.x = SpriteSheetWidth * 6; r.y = SpriteSheetHeight * 0; 
    clipsLeft[6] = r;
    r.x = SpriteSheetWidth * 7; r.y = SpriteSheetHeight * 0; 
    clipsLeft[7] = r;
    r.x = SpriteSheetWidth * 8; r.y = SpriteSheetHeight * 0; 
    clipsLeft[8] = r;
    r.x = SpriteSheetWidth * 9; r.y = SpriteSheetHeight * 0; 
    clipsLeft[9] = r;
    r.x = SpriteSheetWidth * 10; r.y = SpriteSheetHeight * 0; 
    clipsLeft[10] = r;
    r.x = SpriteSheetWidth * 11; r.y = SpriteSheetHeight * 0; 
    clipsLeft[11] = r;

    // rightwards
    r.x = 0; r.y = SpriteSheetHeight * 1; 
    clipsRight[0] = r;
    r.x = SpriteSheetWidth * 1; r.y = SpriteSheetHeight * 1; 
    clipsRight[1] = r;
    r.x = SpriteSheetWidth * 2; r.y = SpriteSheetHeight * 1; 
    clipsRight[2] = r;
    r.x = SpriteSheetWidth * 3; r.y = SpriteSheetHeight * 1; 
    clipsRight[3] = r;
    r.x = SpriteSheetWidth * 4; r.y = SpriteSheetHeight * 1; 
    clipsRight[4] = r;
    r.x = SpriteSheetWidth * 5; r.y = SpriteSheetHeight * 1; 
    clipsRight[5] = r;
    r.x = SpriteSheetWidth * 6; r.y = SpriteSheetHeight * 1; 
    clipsRight[6] = r;
    r.x = SpriteSheetWidth * 7; r.y = SpriteSheetHeight * 1; 
    clipsRight[7] = r;
    r.x = SpriteSheetWidth * 8; r.y = SpriteSheetHeight * 1; 
    clipsRight[8] = r;
    r.x = SpriteSheetWidth * 9; r.y = SpriteSheetHeight * 1; 
    clipsRight[9] = r;
    r.x = SpriteSheetWidth * 10; r.y = SpriteSheetHeight * 1; 
    clipsRight[10] = r;
    r.x = SpriteSheetWidth * 11; r.y = SpriteSheetHeight * 1; 
    clipsRight[11] = r;

    // Downwards
    r.x = 0; r.y = SpriteSheetHeight * 2; 
    clipsDown[0] = r;
    r.x = SpriteSheetWidth * 1; r.y = SpriteSheetHeight * 2; 
    clipsDown[1] = r;
    r.x = SpriteSheetWidth * 2; r.y = SpriteSheetHeight * 2; 
    clipsDown[2] = r;
    r.x = SpriteSheetWidth * 3; r.y = SpriteSheetHeight * 2; 
    clipsDown[3] = r;
    r.x = SpriteSheetWidth * 4; r.y = SpriteSheetHeight * 2; 
    clipsDown[4] = r;
    r.x = SpriteSheetWidth * 5; r.y = SpriteSheetHeight * 2; 
    clipsDown[5] = r;
    r.x = SpriteSheetWidth * 6; r.y = SpriteSheetHeight * 2; 
    clipsDown[6] = r;
    r.x = SpriteSheetWidth * 7; r.y = SpriteSheetHeight * 2; 
    clipsDown[7] = r;
    r.x = SpriteSheetWidth * 8; r.y = SpriteSheetHeight * 2; 
    clipsDown[8] = r;
    r.x = SpriteSheetWidth * 9; r.y = SpriteSheetHeight * 2; 
    clipsDown[9] = r;
    r.x = SpriteSheetWidth * 10; r.y = SpriteSheetHeight * 2; 
    clipsDown[10] = r;
    r.x = SpriteSheetWidth * 11; r.y = SpriteSheetHeight * 2; 
    clipsDown[11] = r;

    // upwards
    r.x = 0; r.y = SpriteSheetHeight * 3; 
    clipsUp[0] = r;
    r.x = SpriteSheetWidth * 1; r.y = SpriteSheetHeight * 3; 
    clipsUp[1] = r;
    r.x = SpriteSheetWidth * 2; r.y = SpriteSheetHeight * 3; 
    clipsUp[2] = r;
    r.x = SpriteSheetWidth * 3; r.y = SpriteSheetHeight * 3; 
    clipsUp[3] = r;
    r.x = SpriteSheetWidth * 4; r.y = SpriteSheetHeight * 3; 
    clipsUp[4] = r;
    r.x = SpriteSheetWidth * 5; r.y = SpriteSheetHeight * 3; 
    clipsUp[5] = r;
    r.x = SpriteSheetWidth * 6; r.y = SpriteSheetHeight * 3; 
    clipsUp[6] = r;
    r.x = SpriteSheetWidth * 7; r.y = SpriteSheetHeight * 3; 
    clipsUp[7] = r;
    r.x = SpriteSheetWidth * 8; r.y = SpriteSheetHeight * 3; 
    clipsUp[8] = r;
    r.x = SpriteSheetWidth * 9; r.y = SpriteSheetHeight * 3; 
    clipsUp[9] = r;
    r.x = SpriteSheetWidth * 10; r.y = SpriteSheetHeight * 3; 
    clipsUp[10] = r;
    r.x = SpriteSheetWidth * 11; r.y = SpriteSheetHeight * 3; 
    clipsUp[11] = r;

    currentFrame = 0;

    // loc->w = SpriteSheetWidth; loc->h = SpriteSheetHeight;
    hitbox.w = width - (width / SpriteSheetWidth)*2; hitbox.h = height - (height / SpriteSheetHeight)*1;
    // setLoc((winW - loc->w) / 2, (MAP_HEIGHT - loc->h) / 2);
    // std::cout << loc->w << " " << loc->h << std::endl;
}

void Yahdu::landSetPos(int x, int y)
{
    x_pos = x;
    y_pos = y - height;
    if (rightDir == 0)
        x_pos -= width;
    else x_pos -= (width - hitbox.w) / 2;
}
void Yahdu::labSetPos(int x, int y)
{
    // slight adjustments based on the next state
    x_pos = x;
    y_pos = y - height;
    if (rightDir == 0)
        x_pos = x - width;
}

void Yahdu::handleEvents()
{
    // KEYDOWN
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_w:
            up = 1;
            // frameUp = 0;
            break;

        case SDLK_s:
            down = 1;
            // frameDown = 0;
            break;

        case SDLK_a:
            left = 1;
            frameLeft = 0;
            break;

        case SDLK_d:
            right = 1;
            frameRight = 0;
            break;
        }

    }

    //KEYUP
    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
        case SDLK_w:
            // frameUp = 0;
            up = 0;
            // dir = 0;
            break;

        case SDLK_s:
            // frameDown = 0;
            down = 0;
            // dir = 1;
            break;

        case SDLK_a:
            frameLeft = 0;
            left = 0;
            dir = 2;
            break;

        case SDLK_d:
            frameRight = 0;
            right = 0;
            dir = 3;
            break;
        }
    }
}

void Yahdu::updateInLand()
{
    // movement when Yahdu is on Land
    if (up && collisionInLand()) y_vel = -vel;        // add to if condition: Yahdu on land
    if (left && right && collisionInLand() && x_vel != 0)
    {
        if (x_vel < 0)
            x_vel += fric; 
        else
            x_vel -= fric;
    }
    // an attempt was made to provide friction when landing from the sky
    // else if (!left && !right && collisionInLand())
    // {
    //     if (x_vel < 0)
    //         x_vel += fric; 
    //     else
    //         x_vel -= fric;
    // }

    // accelerating on land up to the max speed
    else if (left && !right && collisionInLand()) x_vel = -vel;
    else if (!left && right && collisionInLand()) x_vel = vel;

    if (!left && !right && collisionInLand()) x_vel = 0;

    // movement w/ momentum when Yahdu off land
    // aka DI
    if (left && !right && !collisionInLand()) x_vel += -acc / 5;
    else if (!left && right && !collisionInLand()) x_vel += acc / 5;

    // if Yahdu somehow is faster than vel, then its speed will decelerate to vel
    if (collisionInLand() && (x_vel > vel || x_vel < -vel))
    {
        if (x_vel > vel)
            x_vel -= fric;
        if (x_vel < -vel)
            x_vel += fric;
    }
    // updates x coordinate
    x_pos += x_vel / 60;
    // moves Yado's hitbox
    shiftHitbox();

    if (hitbox.x + hitbox.w > LAND_W * 2 / 3 && hitbox.x < LAB_W + LAND_W * 2 / 3 && hitbox.y + hitbox.w > landscapeBaseline - LAB_H)
    {
        // checks if Yahdu's x_pos is a lot greater than the Lab's left entrance to confirm Yahdu entered from the right side of the lab.
        if (x_pos > LAND_W * 2 / 3)
        {
            rightDir = 0;
            std::cout << "rightDir = 1" << std::endl;
        }
        else
        {
            rightDir = 1;
            std::cout << "rightDir = 0" << std::endl;
        }
        setNextState(STATE_LAB);
        return;
    }
    
    // updates y coordinate
    if (!collisionInLand())
        y_vel += acc;
    y_pos += y_vel / 60;
    // moves Yado's hitbox
    shiftHitbox();

    if (collisionInLand())
        y_pos = landscapeBaseline - hitbox.h;

    // collision for x-axis boundary
    if (x_pos < 0) 
    {
        x_pos = 0;
        x_vel = 0;
    }
    if (x_pos + width > LAND_W)
    {
        x_pos = LAND_W - width;
        x_vel = 0;
    }
    
    // updateCam();
    updateFrame();
}

void Yahdu::updateInLab()
{
    // movement when Yahdu is on Land
    if (up && collisionInLab()) y_vel = -vel;        // add to if condition: Yahdu on land
    if (left && right && collisionInLab() && x_vel != 0)
    {
        if (x_vel < 0)
            x_vel += fric; 
        else
            x_vel -= fric;
    }

    // accelerating on land up to the max speed
    else if (left && !right && collisionInLab()) x_vel = -vel;
    else if (!left && right && collisionInLab()) x_vel = vel;

    if (!left && !right && collisionInLab()) x_vel = 0;

    // movement w/ momentum when Yahdu off land
    // aka DI
    if (left && !right && !collisionInLab()) x_vel += -acc / 5;
    else if (!left && right && !collisionInLab()) x_vel += acc / 5;

    // if Yahdu somehow is faster than vel, then its speed will decelerate to vel
    if (collisionInLab() && (x_vel > vel || x_vel < -vel))
    {
        if (x_vel > vel)
            x_vel -= fric;
        if (x_vel < -vel)
            x_vel += fric;
    }
    // if (up && collisionInLab()) y_vel = -vel;        // add to if condition: Yahdu on land
    // if (left && right) x_vel = 0;
    // else if (left && !right) x_vel = -vel;
    // else if (!left && right) x_vel = vel;
    // if (!left && !right) x_vel = 0;

    // updates x coordinate
    x_pos += x_vel / 60;
    // moves Yado's hitbox
    shiftHitbox();

    // updates y coordinate
    if (!collisionInLab())
        y_vel += acc;
    y_pos += y_vel / 60;
    // moves Yado's hitbox
    shiftHitbox();

    if (collisionInLab())
        y_pos = labBaseline - hitbox.h;

    // collision for x-axis boundary
    if (x_pos < 0) 
    {
        rightDir = 0;
        setNextState(STATE_LANDSCAPE);
        return;
    }

    if (x_pos + width > winW)
    {
        rightDir = 1;
        setNextState(STATE_LANDSCAPE);
        return;
    }

    updateFrame();
}

void Yahdu::updateLandCam()
{
    camX = x_pos + (width - winW) / 2;
    // camY = y_pos + (height - winH) / 2;
    
    if (camX < 0) camX = 0;
    // if (camY < 0) camY = 0;
    if (camX > LAND_W - winW) camX = LAND_W - winW;
}

void Yahdu::updateFrame()
{
    // if (up)
    // {
    //     if (++frameUp / 3 >= numFrames)
    //         frameUp = 1;
    // }
    
    // else if (down)
    // {
    //     if (++frameDown / 3 >= numFrames)
    //         frameDown = 1;
    // }
    
    if (left)
    {
        if (++frameLeft / 3 >= numFrames)
            frameLeft = 0;
    }
    
    else if (right)
    {
        if (++frameRight / 3 >= numFrames)
            frameRight = 0;
    }
    
    if (SDL_GetTicks() > lastTime + (int) buffer)
        lastTime = SDL_GetTicks();

    // updateCurrentFrame();
    // updates last frame based on the current frame of the previous frame
    lastFrame = currentFrame;

    // if (up)
    // {
    //     currentFrame = frameUp / 3;
    // }
    // else if (down)
    // {
    //     currentFrame = frameDown / 3;
    // }
    if (left)
    {
        currentFrame = frameLeft / 3;
    }
    else if (right)
    {
        currentFrame = frameRight / 3;
    }

    // assuming no buttons are pressed, the current frame will resort to the last frame, since no animation must be played
    else currentFrame = lastFrame;
}

void Yahdu::shiftHitbox()
{
    // based on texture's rendering location, we define and change the hitbox rectangel
    hitbox.x = x_pos + (width / SpriteSheetWidth)*2;
    hitbox.y = y_pos + (height / SpriteSheetHeight)*1;
}

bool Yahdu::collisionInLand()
{
    if (y_pos >= landscapeBaseline - hitbox.h) return 1;
    return 0;
}

bool Yahdu::collisionInLab()
{
    if (y_pos >= labBaseline - hitbox.h) return 1;
    return 0;
}

void Yahdu::renderLandCam()
{
    // renders camera's POV section of whole landmap
    cam.x = camX; cam.y = camY;
    SDL_RenderCopy(rend, landmap, &cam, NULL);
}

void Yahdu::renderLabCam()
{
    cam.x = 0; cam.y = 0;
    SDL_RenderCopy(rend, labmap, &cam, NULL);
}

void Yahdu::render()
{
    // rendering Yahdu WRT to the cam
    SDL_Rect renderQuad = {x_pos - camX, y_pos - camY, width, height};

    // if (up)
    //     SDL_RenderCopy(rend, SpriteSheet, &clipsUp[currentFrame], &renderQuad);
    // else if (down)
    //     SDL_RenderCopy(rend, SpriteSheet, &clipsDown[currentFrame], &renderQuad);
    // random buffer to stop that annoying spritesheet at the bottom of the screen glitch like wtf m8
    if (left)
        SDL_RenderCopy(rend, SpriteSheet, &clipsLeft[currentFrame], &renderQuad);
    else if (right)
        SDL_RenderCopy(rend, SpriteSheet, &clipsRight[currentFrame], &renderQuad);
    else
    {
        // if (dir == 0)
        //     SDL_RenderCopy(rend, SpriteSheet, &clipsUp[0], &renderQuad);
        // else if (dir == 1)
        //     SDL_RenderCopy(rend, SpriteSheet, &clipsDown[0], &renderQuad);
        if (dir == 2)
            SDL_RenderCopy(rend, SpriteSheet, &clipsLeft[0], &renderQuad);
        else if (dir == 3)
            SDL_RenderCopy(rend, SpriteSheet, &clipsRight[0], &renderQuad);
    }
    // draw baseline in landscape
    // SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    // SDL_RenderDrawLine(rend, 0, landscapeBaseline, LAND_W - 2, landscapeBaseline);
    // yado's rectangel hitbox is rendered :D
    shiftHitbox();
}
