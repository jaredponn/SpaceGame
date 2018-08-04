#include "GameInputMaps.h"
#include "../GameConfig.h"
#include "../Events/GameEvents.h"


// -----------------------------------------
//    private
// -----------------------------------------

static inline void INP_addCameraMovements(struct INP_InputMap *inputMap);

// -----------------------------------------
//    public
// -----------------------------------------

// macro to remove a bit of the boiler plate when creaing new bindings
#define ADD_KEY_RELEASE_BINDING(inputMap, key, function)                       \
	do {                                                                   \
		INP_addKeyReleaseBinding(                                      \
			inputMap,                                              \
			((struct INP_KeyBind){.sdlKey = key,                   \
					      .game_event_func = function}));  \
	} while (0)

#define ADD_KEY_PRESS_BINDING(inputMap, key, function)                         \
	do {                                                                   \
		INP_addKeyPressBinding(                                        \
			inputMap,                                              \
			((struct INP_KeyBind){.sdlKey = key,                   \
					      .game_event_func = function}));  \
	} while (0)


void INP_setDefaultMap(struct INP_InputMap *inputMap)
{
	INP_clearInputMap(inputMap);

	// binding key 1 to create a solar station
	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_1,
				EVT_trySpawnNewSolarStation);

	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_A,
				EVT_spawnNewSolarStation);

	/** INP_addKeyPressBinding( */
	/**         inputMap, ((struct INP_KeyBind){ */
	/**                           .sdlKey = SDL_SCANCODE_B, */
	/**                           .gameEvent = (Event){.type =
	 * EVT_SpawnB}})); */

	INP_addMouseKeyPressBinding(
		inputMap,
		((struct INP_MouseKeyBind){
			.sdlButton = SDL_BUTTON_LEFT,
			.game_event_func = EVT_leftMousePressButtonHandler}));

	INP_addCameraMovements(inputMap);
}

// -----------------------------------------
//    private
// -----------------------------------------

static inline void INP_addCameraMovements(struct INP_InputMap *inputMap)
{
	// moving the camera with arrow keys
	ADD_KEY_PRESS_BINDING(inputMap, SDL_SCANCODE_UP,
			      EVT_changeCameraVelocityUp);

	ADD_KEY_PRESS_BINDING(inputMap, SDL_SCANCODE_DOWN,
			      EVT_changeCameraVelocityDown);

	ADD_KEY_PRESS_BINDING(inputMap, SDL_SCANCODE_LEFT,
			      EVT_changeCameraVelocityLeft);

	ADD_KEY_PRESS_BINDING(inputMap, SDL_SCANCODE_RIGHT,
			      EVT_changeCameraVelocityRight);

	// deccelerating on release
	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_UP,
				EVT_decelerateCameraUp);

	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_DOWN,
				EVT_decelerateCameraDown);

	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_LEFT,
				EVT_decelerateCameraLeft);

	ADD_KEY_RELEASE_BINDING(inputMap, SDL_SCANCODE_RIGHT,
				EVT_decelerateCameraRight);
}
