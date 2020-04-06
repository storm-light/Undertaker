#ifndef _GLOBALVARS_H_
#define _GLOBALVARS_H_

#include "GameState.h"
#include "Yahdu.h"

#define LAND_W (3840)

#define TILE_SIZE (16)

#define LAB_W (320)
#define LAB_H (160)

extern int labBaseline;
extern int landscapeBaseline;

extern int stateID;
extern int rightDir;

extern int nextState;

extern GameState * currentState;

extern SDL_Texture * landmap;
extern SDL_Texture * labmap;

extern SDL_Renderer * rend;
extern SDL_Window * win;

extern SDL_Event event;

extern int winW;
extern int winH;

//Game states
enum GameStates
{
    STATE_NULL,
    STATE_TITLE,
    STATE_LANDSCAPE,
    STATE_LAB,
    // STATE_GRAVEYARD,
    STATE_EXIT,
};

// extern Yahdu * yahdu;
// extern Cam cam;

#endif
