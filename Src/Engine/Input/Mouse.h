#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Lib/V2.h"
#include "Lib/GUI.h"

// -----------------------------------------
//    types
// -----------------------------------------

// -----------------------------------------
//    Global mouse state type (should be read only)
// -----------------------------------------

struct INP_MouseState;
struct INP_MouseState {
	/**current state things*/
	struct V2 mouse_position;		/**< current mouse position */
	struct V2 scroll_direction;		/**< currnet scroll direction */
	bool mouse_button_state[SDL_BUTTON_X2]; /**< mouse's button state
					      (pressed or down) */

	/**gui interactions*/
	struct GObject
		*focus; /**< current thing focued in the gui. NULL
				       denotes the gui is not being focued */

	/** previous state */
	struct V2 old_scroll_direction; /**< old scroll direction (useful for
					   scrolling) */
	struct V2 old_mouse_position; /**< old mouse position (useful for things
					 like drag) */
};

// -----------------------------------------
//    functions
// -----------------------------------------

// initilizes the global mouse state
void INP_initMouseState();

// get the raw mouse position from SDL
struct V2 INP_getRawMousePosition();

// get the mouuse position and adjusts it to the proper screen coordinates,
// provided the camera position is given
struct V2 INP_getWorldMousePosition(const struct V2 *);

// get scroll direction
const struct V2 *INP_getScroll();

// gets the change in the raw mouse position from the old mouse position
struct V2 INP_getChangeInRawMousePosition();

// gets the change in the world mouse position
struct V2 INP_getChangeInWorldMousePosition(const struct V2 *);

// set focus
void INP_setMouseFocus(const struct GObject *);

// gets the current focus
const struct GObject *INP_getMouseFocus();

// left mouse button pressing will be ver comomn, so a conveinence func
bool INP_isLeftMouseButtonPressed();

// uint8 must be a SDL_MouseButtonEvent.button
bool INP_isMouseButtonPressed(const Uint8);

// -----------------------------------------
//    interal usage functions
// -----------------------------------------

// sets the mouse position -- interal usage only
void INP_setMousePosition(float x, float y);

// sets the scroll direction -- interal usage only
void INP_setScrollDirection(float x, float y);

// sets the mouse_button_state. The Uint8 is the the enume of a
// SDL_MouseButtonEvent.button
void INP_setMouseButtonState(Uint8, bool);
