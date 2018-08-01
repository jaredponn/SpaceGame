#pragma once
#include <SDL2/SDL.h>

#include "InputMap.h"
#include "Lib/V2.h"
#include "../ExtraState/EngineExtraState.h"

/**
 * Input handler -- contains functionality to parse an InputMap into game
 * events. Also includes the mouse's position and scroll direction with const
 * methods to get it, and methods for getting the window size
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
void INP_parseInputs(SDL_Event *, struct INP_InputMap *, struct EventManager *);

// get the raw mouse position from SDL
const struct V2 *INP_getRawMousePosition();

// get the mouuse position and adjusts it to the proper screen coordinates,
// provided the camera position is given
struct V2 INP_getScreenMousePosition(const struct V2 *);

// get scroll direction
const struct V2 *INP_getScroll();

// gets the window dimensions
struct V2 INP_getScreenSize();
