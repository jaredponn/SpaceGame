#include "GameInputMaps.h"
#include "../EventManager/EventManager.h"

#define CAMERA_VELOCITY 1000
#define CAMERA_ACCELERATION_DECAY 3000

// -----------------------------------------
//    private
// -----------------------------------------

static inline void INP_addCameraMovements(struct INP_InputMap *inputMap);

// -----------------------------------------
//    public
// -----------------------------------------

void INP_setDefaultMap(struct INP_InputMap *inputMap)
{
	INP_clearInputMap(inputMap);

	// testing spawning
	INP_addKeyReleaseBinding(
		inputMap, ((struct INP_KeyBind){
				  .sdlKey = SDL_SCANCODE_A,
				  .gameEvent = (Event){.type = EVT_SpawnA}}));
	INP_addKeyPressBinding(
		inputMap, ((struct INP_KeyBind){
				  .sdlKey = SDL_SCANCODE_B,
				  .gameEvent = (Event){.type = EVT_SpawnB}}));

	INP_addMouseKeyPressBinding(
		inputMap, ((struct INP_MouseKeyBind){
				  .sdlButton = SDL_BUTTON_LEFT,
				  .gameEvent = (Event){.type = EVT_SpawnB}}));

	INP_addCameraMovements(inputMap);
}

// -----------------------------------------
//    private
// -----------------------------------------

static inline void INP_addCameraMovements(struct INP_InputMap *inputMap)
{
	// moving the camera with arrow keys
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_UP, /**< pressing up */
			.gameEvent = (Event){
				.type = EVT_CameraVelocity,
				.camera_velocity = {.x = 0,
						    .y = -CAMERA_VELOCITY}}}));
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_DOWN,
			.gameEvent = (Event){
				.type = EVT_CameraVelocity,
				.camera_velocity = {.x = 0,
						    .y = CAMERA_VELOCITY}}}));
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_LEFT,
			.gameEvent = (Event){
				.type = EVT_CameraVelocity,
				.camera_velocity = {.x = -CAMERA_VELOCITY,
						    .y = 0}}}));
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_RIGHT,
			.gameEvent = (Event){
				.type = EVT_CameraVelocity,
				.camera_velocity = {.x = CAMERA_VELOCITY,
						    .y = 0}}}));

	/** INP_addKeyReleaseBinding( */
	/**         inputMap, */
	/**         ((struct INP_KeyBind){ */
	/**                 .sdlKey = SDL_SCANCODE_UP, [>< releasing up <] */
	/**                 .gameEvent = (Event){ */
	/**                         .type = EVT_CameraMovement, */
	/**                         .camera_velocity = {.x = 0, */
	/**                                             .y =
	 * CAMERA_VELOCITY}}})); */
	/**  */
	/** INP_addKeyReleaseBinding( */
	/**         inputMap, */
	/**         ((struct INP_KeyBind){ */
	/**                 .sdlKey = SDL_SCANCODE_DOWN, [>< releasing down <]
	 */
	/**                 .gameEvent = (Event){ */
	/**                         .type = EVT_CameraMovement, */
	/**                         .camera_velocity = {.x = 0, */
	/**                                             .y =
	 * -CAMERA_VELOCITY}}})); */
	/** INP_addKeyReleaseBinding( */
	/**         inputMap, */
	/**         ((struct INP_KeyBind){ */
	/**                 .sdlKey = SDL_SCANCODE_LEFT, [>< releasing left <]
	 */
	/**                 .gameEvent = (Event){ */
	/**                         .type = EVT_CameraMovement, */
	/**                         .camera_velocity = {.x = CAMERA_VELOCITY, */
	/**                                             .y = 0}}})); */
	INP_addKeyReleaseBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_RIGHT, /**< releasing right */
			.gameEvent =
				(Event){.type = EVT_CameraDecelerate,
					.camera_velocity = {
						.x = -CAMERA_ACCELERATION_DECAY,
						.y = 0}}}));
}
