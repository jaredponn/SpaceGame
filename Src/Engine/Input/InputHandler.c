#include "InputHandler.h"
#include "Mouse.h"

// -----------------------------------------
//    Procedures
// -----------------------------------------


void INP_parseInputs(SDL_Event *sdlEvent, struct INP_InputMap *inputMap,
		     struct CPT_Components *components,
		     struct RSC_ResourceRegistry *resources,
		     struct EXS_ExtraState *extraState)
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
	INP_setScrollDirection(0, 0);

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
						       .sdlKey) {
						KeyBindVector_get(
							&inputMap->keyReleaseMappings,
							i)
							.game_event_func(
								components,
								resources,
								extraState);
					}
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
						KeyBindVector_get(
							&inputMap->keyPressMappings,
							i)
							.game_event_func(
								components,
								resources,
								extraState);
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
					MouseKeyBindVector_get(
						&inputMap->mouseButtonPressMappings,
						i)
						.game_event_func(components,
								 resources,
								 extraState);

				INP_setMouseButtonState(sdlEvent->button.button,
							true);
			}
			break;

		case SDL_MOUSEBUTTONUP:
			for (size_t i = 0; i < mouseKeyReleaseVecLength; ++i) {
				if (sdlEvent->button.button
				    == MouseKeyBindVector_get(
					       &inputMap->mouseButtonReleaseMappings,
					       i)
					       .sdlButton)
					MouseKeyBindVector_get(
						&inputMap->mouseButtonReleaseMappings,
						i)
						.game_event_func(components,
								 resources,
								 extraState);
				INP_setMouseButtonState(sdlEvent->button.button,
							false);
			}
			break;

		case SDL_MOUSEWHEEL:
			INP_setScrollDirection((float)sdlEvent->wheel.x,
					       (float)sdlEvent->wheel.y);
			inputMap->mouseScrollEvent(components, resources,
						   extraState);
			break;

		case SDL_MOUSEMOTION:
			INP_setMousePosition((float)sdlEvent->button.x,
					     (float)sdlEvent->button.y);

			inputMap->mouseMovementEvent(components, resources,
						     extraState);
			break;
		case SDL_QUIT: {
			exit(1);
		}

		default:
			break;
		}
	}
}
