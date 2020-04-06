#include <iostream>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "HelperFunctions.h"
#include "GlobalVars.h"
#include "Lab.h"

Lab::Lab()
{
    bg = loadTexture(rend, "Lab.png");
    labmap = bg;

    baselvl = winH / 2;

    yahdu = new Yahdu();

    if (rightDir == 1)
        yahdu->labSetPos(0, baselvl);
    else
        yahdu->labSetPos(winW, baselvl);
}

Lab::~Lab()
{
    SDL_DestroyTexture(bg);
    yahdu->~Yahdu();
}

void Lab::handleEvents()
{
    // while there are any events to process
    while (SDL_PollEvent(&event))
    {
        yahdu->handleEvents();
        // if user wants to quit
        if (event.type == SDL_QUIT)
        {
            //Quit the program
            setNextState(STATE_EXIT);
        }
        // if the user pressed enter
        else if (event.type == SDL_KEYDOWN) 
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                // to the landscape!
                setNextState(STATE_LANDSCAPE);
                rightDir = 0;
                break;
            case SDLK_RIGHT:
                // to the landscape!
                setNextState(STATE_LANDSCAPE);
                rightDir = 1;
                break;
            }
    }
}

void Lab::update()
{
    yahdu->updateInLab();
}

void Lab::render()
{
    // render background
    SDL_RenderCopy(rend, bg, NULL, NULL);

    // yahdu->renderLabCam();
    yahdu->render();
}
