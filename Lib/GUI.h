#pragma once
#include "GenericVector.h"
#include "V2.h"
#include <SDL2/SDL.h>

/**
 * Structs / functions for creating a GUI (buttons, callbacks, menus)
 */

// -----------------------------------------
//    macros
// -----------------------------------------
VECTOR_DECLARE(struct GUIObject, GUIObject)


// -----------------------------------------
//    types
// -----------------------------------------

struct GUIObject {
	// parent. NULL if there is no parent
	struct GUIObject *parent;
	struct GUIObjectVector children;

	/** appearance attributes*/
	float x; /**< relative x position in parent from 0-1 */
	float y; /**< relative y position in parent from 0-1 */
	float w; /**< width */
	float h; /**< height */

	void (*show)(void *);

	/** callback functions*/
	void (*focus_out_event)(void *);
	void (*focus_in_event)(void *);

	void (*mouse_release_event)(void *);
	void (*mouse_press_event)(void *);

	void (*mouse_over_event)(void *);
};

void GIU_new_object(struct GUIObject *);

// methods to render the buttons
void GUI_show(struct GUIObject *);
void GUI_show_all(struct GUIObject *);

//
void GUI_container_add(struct GUIObject *, struct GUIObject *);
