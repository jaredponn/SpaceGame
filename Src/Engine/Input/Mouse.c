#include "Mouse.h"

// static read only mouse position
static struct INP_MouseState globalMouseState;

void INP_initMouseState()
{
	// setting all values to 0
	memset(&globalMouseState, 0, sizeof globalMouseState);
}

struct V2 INP_getRawMousePosition()
{

	return globalMouseState.mouse_position;
}

struct V2 INP_getWorldMousePosition(const struct V2 *cameraPos)
{

	struct V2 rawMousePosition = INP_getRawMousePosition();
	return V2_add(&rawMousePosition, cameraPos);
}

const struct V2 *INP_getScroll()
{
	return &globalMouseState.scroll_direction;
}

void INP_setMouseFocus(const struct GObject *gobj)
{
	globalMouseState.focus = (struct GObject *)gobj;
}

const struct GObject *INP_getMouseFocus()
{
	return globalMouseState.focus;
}

struct V2 INP_getChangeInRawMousePosition()
{
	return V2_sub(&globalMouseState.mouse_position,
		      &globalMouseState.old_mouse_position);
}

struct V2 INP_getChangeInWorldMousePosition(const struct V2 *cameraPosition)
{

	// world coordinate of the current mouse position
	struct V2 curMousePosition = INP_getRawMousePosition();
	struct V2 curWorldMousePosition =
		V2_add(&curMousePosition, cameraPosition);

	// world coordinate of the old mouse position
	struct V2 oldMousePosition = globalMouseState.old_mouse_position;
	struct V2 oldWorldMousePosition =
		V2_add(&oldMousePosition, cameraPosition);

	// returning the change in the mouse coordinate
	return V2_sub(&curWorldMousePosition, &oldWorldMousePosition);
}

bool INP_isMouseButtonPressed(const Uint8 btn)
{
	return globalMouseState.mouse_button_state[btn];
}

bool INP_isLeftMouseButtonPressed()
{
	return globalMouseState.mouse_button_state[SDL_BUTTON_LEFT];
}


// Uint8 mouse_button_state[X2_MOUSE]; /**< mouse's button state */
// -----------------------------------------
//    internal usage functions
// -----------------------------------------

void INP_setMousePosition(float x, float y)
{
	globalMouseState.old_mouse_position = globalMouseState.mouse_position;
	globalMouseState.mouse_position = (struct V2){.x = x, .y = y};
}

void INP_setScrollDirection(float x, float y)
{
	globalMouseState.old_scroll_direction =
		globalMouseState.scroll_direction;
	globalMouseState.scroll_direction = (struct V2){.x = x, .y = y};
}

void INP_setMouseButtonState(Uint8 btn, bool val)
{
	globalMouseState.mouse_button_state[btn] = val;
}
