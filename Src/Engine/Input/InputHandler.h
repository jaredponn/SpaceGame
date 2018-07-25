#pragma once
#include <SDL2/SDL.h>
#include "InputMap.h"
#include "Lib/V2.h"

/**
 * Input handler -- contains functionality to parse an InputMap into game
 * events. Also includes the mouse's position and scroll direction with const
 * methods to get it.
 */

// -----------------------------------------
//    Global mouse state type (should be read only)
// -----------------------------------------
struct INP_MouseState;
struct INP_MouseState {
        struct V2 mouse_position;
        struct V2 scroll_direction;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initilizes the global mouse state
void INP_initMouseState();

// parses the SDL_Event's and sends them to the Event_Vector
void INP_parseInputs(SDL_Event*, struct INP_InputMap*, struct EventManager*);

// getting the mouse position
const struct V2* INP_getMousePosition();

// get scroll direction
const struct V2* INP_getScroll();
