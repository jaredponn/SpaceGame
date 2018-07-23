#pragma once

#include <SDL2/SDL.h>
#include "../EventManager/EventManager.h"

#include "Lib/GenericVector.h"
/**
 * Input map -- structs, types, procedures for an input map.
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
        Uint8 sdlButton; /**< the SDL mousebutton that was pressed:
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
        struct KeyBind_Vector keyPressMappings;   /**< vector of the bindings
                                                  given   in a key up event */
        struct KeyBind_Vector keyReleaseMappings; /**< vector of the bindings
                                                given in a keydown event */
        struct MouseKeyBind_Vector
            mouseButtonPressMappings; /**< vector of bindings when the mouse
                                      button is released (SDL_RELEASED) */
        struct MouseKeyBind_Vector
            mouseButtonReleaseMappings; /**< vector of bindings when the mouse
                                      button is released (SDL_PRESSED)*/

        INP_MouseMovement mouseMovementEvent; /**< on mouse event gameevent  */

        INP_MouseScroll
            mouseScrollEvent; /**< on mouse scroll event gameevent */
};

// -----------------------------------------
//    Procedures
// -----------------------------------------

// initlizes the input map
void INP_initInputMap(struct INP_InputMap*);

// clears the input map
void INP_clearInputMap(struct INP_InputMap*);

// initlizes the input map, and the global state variables for the mouse
void ECS_freeInputMap(struct INP_InputMap*);

// -----------------------------------------
//    Procedures for modifying the key map
// -----------------------------------------

/**
 * the add<..>Binding functions add a binding to the manager and checks if it is
 * already added. if it is already added, it will replace the current binding
 */
void INP_addKeyReleaseBinding(struct INP_InputMap*, const struct INP_KeyBind);
void INP_addKeyPressBinding(struct INP_InputMap*, const struct INP_KeyBind);

void INP_addMouseKeyReleaseBinding(struct INP_InputMap*,
                                   const struct INP_MouseKeyBind);
void INP_addMouseKeyPressBinding(struct INP_InputMap*,
                                 const struct INP_MouseKeyBind);

void INP_setMouseMovementEvent(struct INP_InputMap*, const Event);
void INP_setMouseScrollEvent(struct INP_InputMap*, const Event);
