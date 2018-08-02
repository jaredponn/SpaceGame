#pragma once

#include <SDL2/SDL.h>
#include "Lib/V2.h"
#include "Lib/GUI.h"


// -----------------------------------------
//    Global mouse state type (should be read only)
// -----------------------------------------
struct INP_MouseState;
struct INP_MouseState {
	struct V2 mouse_position;   /**< current mouse position */
	struct V2 scroll_direction; /**< currnet scroll direction */

	struct GObject
		*focus;		      /**< current thing focued in the gui. NULL
						     denotes the gui is not being focued */
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

// -----------------------------------------
//    interal usage functions
// -----------------------------------------

// sets the mouse position -- interal usage only
void INP_setMousePosition(float x, float y);

// sets the scroll direction -- interal usage only
void INP_setScrollDirection(float x, float y);
