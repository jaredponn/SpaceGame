#include "GameInputMaps.h"
#include "../EventManager/EventManager.h"
#include "../GameConfig.h"


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

	// binding key 1 to create a solar station
	INP_addKeyReleaseBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_1,
			.gameEvent = (Event){
				.type = EVT_Build,
				.build = (EVT_BuildSignal){
					.station_type = SOLAR_STATION,
					.gold_price = SPACE_STATION_PRICE}}}));
	/** INP_addKeyPressBinding( */
	/**         inputMap, ((struct INP_KeyBind){ */
	/**                           .sdlKey = SDL_SCANCODE_B, */
	/**                           .gameEvent = (Event){.type =
	 * EVT_SpawnB}})); */

	INP_addMouseKeyPressBinding(
		inputMap,
		((struct INP_MouseKeyBind){
			.sdlButton = SDL_BUTTON_LEFT,
			.gameEvent = (Event){.type = EVT_LeftMousePress}}));

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
			.gameEvent = (Event){.type = EVT_CameraYVelocity,
					     .camera_y_velocity =
						     -CAMERA_VELOCITY}}));
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_DOWN,
			.gameEvent = (Event){.type = EVT_CameraYVelocity,
					     .camera_y_velocity =
						     CAMERA_VELOCITY}}));
	INP_addKeyPressBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_LEFT,
			.gameEvent = (Event){.type = EVT_CameraXVelocity,
					     .camera_x_velocity =
						     -CAMERA_VELOCITY}}));
	INP_addKeyPressBinding(
		inputMap, ((struct INP_KeyBind){
				  .sdlKey = SDL_SCANCODE_RIGHT,
				  .gameEvent = (Event){
					  .type = EVT_CameraXVelocity,
					  .camera_x_velocity = CAMERA_VELOCITY,
				  }}));

	INP_addKeyReleaseBinding(
		inputMap, ((struct INP_KeyBind){
				  .sdlKey = SDL_SCANCODE_UP,
				  .gameEvent = (Event){
					  .type = EVT_CameraYDecelerate,
					  .camera_y_velocity =
						  CAMERA_ACCELERATION_DECAY}}));

	INP_addKeyReleaseBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_DOWN, /**< releasing down */
			.gameEvent =
				(Event){.type = EVT_CameraYDecelerate,
					.camera_y_velocity =
						-CAMERA_ACCELERATION_DECAY}}));
	INP_addKeyReleaseBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_LEFT, /**< releasing left */
			.gameEvent = (Event){
				.type = EVT_CameraXDecelerate,
				.camera_x_velocity = CAMERA_ACCELERATION_DECAY,
			}}));
	INP_addKeyReleaseBinding(
		inputMap,
		((struct INP_KeyBind){
			.sdlKey = SDL_SCANCODE_RIGHT, /**< releasing right */
			.gameEvent = (Event){
				.type = EVT_CameraXDecelerate,
				.camera_x_velocity = -CAMERA_ACCELERATION_DECAY,
			}}));
}
