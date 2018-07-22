#pragma once
#include <SDL2/SDL.h>
#include "../EventManager/EventManager.h"
#include "Lib/GenericVector.h"
#include "Lib/V2.h"

/**
 * Input handler
 */

// -----------------------------------------
//    Raw events to game event bindings
// -----------------------------------------

// bindings from an SDL_Key keyboard event to a game event
struct INP_KeyBind;
struct INP_KeyBind {
        Uint32 sdlKey;   /**< the key event in SDL:
                            https://wiki.libsdl.org/SDL_Scancode  */
        Event gameEvent; /**< the game event that corrosponds to the SDL event*/
};
VECTOR_DECLARE(struct INP_KeyBind, KeyBind)

// bindings from a SDL mouse button event
struct INP_MouseKeyBind;
struct INP_MouseKeyBind {
        Uint8 button;    /**< the SDL mousebutton that was pressed:
                            SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, SDL_BUTTON_RIGHT,
                            SDL_BUTTONX1, SDL_BUTTON_X2 */
        Event gameEvent; /**< the game event that corrosponds to the SDL event*/
};
VECTOR_DECLARE(struct INP_MouseKeyBind, MouseKeyBind)

// game event to execute when the mouse is moved
// struct INP_MouseMovement;
// struct INP_MouseMovement {
//         Event gameEvent; [>*< the game event <]
// };
typedef Event INP_MouseMovement;

// game event to execute when the mouse wheel is moved
// struct INP_MouseScroll;
// struct INP_MouseScroll {
//         Event gameEvent; [>*< the game event <]
// };
typedef Event INP_MouseScroll;

// -----------------------------------------
//    Input map
// -----------------------------------------
struct INP_InputMap;
struct INP_InputMap {
        struct KeyBind_Vector keyUpMappings;   /**< vector of the bindings given
                                                  in a key up event */
        struct KeyBind_Vector keyDownMappings; /**< vector of the bindings given
                                                in a keydown event */
        struct MouseKeyBind_Vector
            mouseButtonUpMappings; /**< vector of bindings when the mouse button
                                      is released (SDL_RELEASED) */
        struct MouseKeyBind_Vector
            mouseButtonDownMappings; /**< vector of bindings when the mouse
                                      button is released (SDL_PRESSED)*/

        INP_MouseMovement mouseMovementEvent; /**< on mouse event gameevent  */

        INP_MouseScroll
            mouseScrollEvent; /**< on mouse scroll event gameevent */
};

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

// initlizes the input map, and the global state variables for the mouse
void ECS_InputMap_init(struct INP_InputMap*);

// clears the input map
void INP_clearInputMap(struct INP_InputMap*);

// parses the SDL_Event's and sends them to the Event_Vector
void INP_parseInputs(SDL_Event*, struct INP_InputMap*, struct Event_Vector*);

// getting the mouse position
const struct V2* INP_getMousePosition();

// get scroll direction
const struct V2* INP_getScroll();

// initlizes the input map, and the global state variables for the mouse
void ECS_free_InputMap(struct INP_InputMap*);
