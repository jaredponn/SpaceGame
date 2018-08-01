#include "InputHandler.h"

// stattic read only global variable of the mouse's position and scroll
// direction
static struct INP_MouseState globalMouseState;

// -----------------------------------------
//    Procedures
// -----------------------------------------

void INP_initMouseState()
{
	globalMouseState =
		(struct INP_MouseState){.mouse_position = (struct V2){0, 0},
					.scroll_direction = (struct V2){0, 0}};
}

void INP_parseInputs(SDL_Event *sdlEvent, struct INP_InputMap *inputMap,
		     struct EventManager *eventManager)
{
	// getting the vectors' lengths
	size_t keyReleaseVecLength =
		KeyBindVector_size(&inputMap->keyReleaseMappings);
	size_t keyPressVecLength =
		KeyBindVector_size(&inputMap->keyPressMappings);

	size_t mouseKeyPressedVecLength =
		MouseKeyBindVector_size(&inputMap->mouseButtonPressMappings);
	size_t mouseKeyReleaseVecLength =
		MouseKeyBindVector_size(&inputMap->mouseButtonReleaseMappings);

	// resetting the global mouse scrolling state
	globalMouseState.scroll_direction.x = 0;
	globalMouseState.scroll_direction.y = 0;

	while (SDL_PollEvent(sdlEvent)) {
		// changes the button states (mouse and keyboard)
		switch (sdlEvent->type) {
		case SDL_KEYUP:
			if (sdlEvent->key.repeat == 0) {
				for (size_t i = 0; i < keyReleaseVecLength;
				     ++i) {
					if (sdlEvent->key.keysym.scancode
					    == KeyBindVector_get(
						       &inputMap->keyReleaseMappings,
						       i)
						       .sdlKey)
						EventManager_push_back(
							eventManager,
							KeyBindVector_get(
								&inputMap->keyReleaseMappings,
								i)
								.gameEvent);
				}
			}
			break;

		case SDL_KEYDOWN:
			if (sdlEvent->key.repeat == 0) {
				for (size_t i = 0; i < keyPressVecLength; ++i) {
					if (sdlEvent->key.keysym.scancode
					    == KeyBindVector_get(
						       &inputMap->keyPressMappings,
						       i)
						       .sdlKey)
						EventManager_push_back(
							eventManager,
							KeyBindVector_get(
								&inputMap->keyPressMappings,
								i)
								.gameEvent);
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			for (size_t i = 0; i < mouseKeyPressedVecLength; ++i) {
				if (sdlEvent->button.button
				    == MouseKeyBindVector_get(
					       &inputMap->mouseButtonPressMappings,
					       i)
					       .sdlButton)
					EventManager_push_back(
						eventManager,
						MouseKeyBindVector_get(
							&inputMap->mouseButtonPressMappings,
							i)
							.gameEvent);
			}
			break;

		case SDL_MOUSEBUTTONUP:
			for (size_t i = 0; i < mouseKeyReleaseVecLength; ++i) {
				if (sdlEvent->button.button
				    == MouseKeyBindVector_get(
					       &inputMap->mouseButtonReleaseMappings,
					       i)
					       .sdlButton)
					EventManager_push_back(
						eventManager,
						MouseKeyBindVector_get(
							&inputMap->mouseButtonReleaseMappings,
							i)
							.gameEvent);
			}
			break;

		case SDL_MOUSEWHEEL:
			globalMouseState.scroll_direction =
				(struct V2){.x = (float)sdlEvent->wheel.x,
					    .y = (float)sdlEvent->wheel.y};

			EventManager_push_back(eventManager,
					       inputMap->mouseScrollEvent);
			break;

		case SDL_MOUSEMOTION:
			globalMouseState.mouse_position =
				(struct V2){.x = (float)sdlEvent->button.x,
					    .y = (float)sdlEvent->button.y};

			EventManager_push_back(eventManager,
					       inputMap->mouseMovementEvent);
			break;
		case SDL_QUIT: {
			exit(1);
		}

		default:
			break;
		}
	}
}

const struct V2 *INP_getRawMousePosition()
{
	return &globalMouseState.mouse_position;
}

struct V2 INP_getScreenMousePosition(const struct V2 *cameraPos)
{

	return V2_add(INP_getRawMousePosition(), cameraPos);
}

const struct V2 *INP_getScroll()
{
	return &globalMouseState.scroll_direction;
}

struct V2 INP_getScreenSize()
{
	SDL_DisplayMode mode;
	if (SDL_GetCurrentDisplayMode(0, &mode) == 0) {
		return (struct V2){.x = mode.w, .y = mode.h};
	} else {
		// maybe addsome proper error handling
		printf("\nerror getting screen size in " __FILE__ "\n");
		return (struct V2){.x = mode.w, .y = mode.h};
	}
}
