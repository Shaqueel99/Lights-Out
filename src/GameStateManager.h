
#pragma once

#include "AEEngine.h"

//Game State List
enum
{
	GS_SPLASH = 0,
	GS_MAINMENU,
	GS_RESTART,
	GS_GAMEPLAY, // 2 different game states to break out of game loop
	GS_GAMEPLAY2,		
	GS_QUIT
};

//Declaring type int game state statuses
extern unsigned int gamestateInit;
extern unsigned int gamestateCurr;
extern unsigned int gamestatePrev;
extern unsigned int gamestateNext;

//Declaring function pointers to game state functions
extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

//Declaring GSM functions
void GameStateManagerInit(unsigned int gamestateInit = GS_MAINMENU);
void GameStateManagerUpdate();


inline void EmptyFunction() { ; }
