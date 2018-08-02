#pragma once
#include <SDL2/SDL.h>

#include "InputMap.h"
#include "Lib/V2.h"
#include "../ExtraState/EngineExtraState.h"

/**
 * Input handler -- contains functionality to parse an InputMap into game
 * events.
 */


// -----------------------------------------
//    Procedures
// -----------------------------------------

// parses the SDL_Event's and sends them to the Event_Vector
void INP_parseInputs(SDL_Event *, struct INP_InputMap *, struct EventManager *);
