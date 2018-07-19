#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "Lib/V2.h"
// -----------------------------------------
//    Contains functions for getting keyboard and mouse input
// -----------------------------------------

// -----------------------------------------
//    Types
// -----------------------------------------

// usefule docuemtation: https://wiki.libsdl.org/SDL_MouseButtonEvent
struct INP_Mouse {
        struct V2 position;
        Uint8 button; /* the button that changed, it may be: SDL_BUTTON_LEFT,
                       * SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT, SDL_BUTTON_X1,
                       * SDL_BUTTON_X2. */
        Uint8 state;  /*the state of the button. SDL_PRESSED or SDL_RELEASED*/
};

// useful documetation: https://wiki.libsdl.org/SDL_MouseWheelEvent
struct INP_Scroll {
        struct V2 scroll_direction;
};
struct INP_Mouse_State {
        struct INP_Mouse mouse;
        struct INP_Scroll scroll;
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

/* When checking for what key is pressed down, this system uses SDL's scancodes
 *
 * SDL SCAN CODES: https://wiki.libsdl.org/SDL_Scancode
 *
 */

// updates keyboard state
void INP_updateInputState(SDL_Event*);

// updates keybaor dstate. Must be called after the event handler
void INP_updateOldState();

// returns a const pointer to the keys
const Uint32* INP_getCurrKeys();
// returns a const pointer to the mouse state
const struct INP_Mouse_State* INP_getCurrMouseState();

// keyboard detection tap methods....
bool INP_onKeyReleaseTap(SDL_Scancode);
bool INP_onKeyPressTap(SDL_Scancode);

// mouse detection tap methods (SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE,
// SDL_BUTTON_RIGHT, SDL_BUTTON_X1, SDL_BUTTON_X2.)
bool INP_onMouseReleaseTap(Uint8);
bool INP_onMousePressTap(Uint8 button);

// getting the mouse position
const struct V2* INP_getMousePosition();

// get scroll
const struct V2* INP_getScroll();
