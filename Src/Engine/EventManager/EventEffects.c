#include "EventEffects.h"
#include "../Input/InputHandler.h"

// returns the sign of a value
#define SIGN(x) ((x > 0) - (x < 0))

// -----------------------------------------
//    private
// -----------------------------------------


// -----------------------------------------
//    public
// -----------------------------------------

#define TEST_RECT_ATTR                                                         \
	CPT_addAcceleration(components, &(Acceleration){.x = 0, .y = -2});     \
                                                                               \
	CPT_addVelocity(components, &(Velocity){.x = 0, .y = -2});             \
                                                                               \
	Position transform = (Position){.x = 50, .y = 50};                     \
	struct V2 tmppp = INP_getScreenMousePosition(                          \
		&extrastate->camera.camera_position);                          \
	Position tmppos = V2_sub((const Position *)&tmppp, &transform);        \
	CPT_addPosition(components, &tmppos);                                  \
                                                                               \
	CPT_addAppearance0(                                                    \
		components,                                                    \
		&(struct Appearance){                                          \
			.texture = resources->cResources.cTextures.planet1,    \
			.srcrect =                                             \
				(SDL_Rect){                                    \
					.x = 0, .y = 0, .w = 1042, .h = 1042}, \
			.dstrect = (SDL_Rect){                                 \
				.x = 0, .y = 0, .w = 100, .h = 100}});


void EVT_spawnTestARect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	CPT_addCircAabb0(components,
			 &(struct CircAabb){.center = tmppos, .radius = 50});
}

void EVT_spawnTestBRect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	// adding brectaabb
	/** CPT_addRectAabb1( */
	/**         components, */
	/**         &(struct RectAabb){ */
	/**                 .pMin = *(struct V2 *)&tmppos, */
	/**                 .pMax = V2_add((struct V2 *)&tmppos, */
	/**                                &(struct V2){.x = 100, .y = 100})});
	 */

	CPT_addCircAabb1(components,
			 &(struct CircAabb){.center = tmppos, .radius = 50});
}

void EVT_changeCameraXVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXVelocitySignal cameraMovementSignal)
{
	extraState->camera.camera_velocity.x = cameraMovementSignal;
	extraState->camera.camera_acceleration.x = 0;
}

void EVT_changeCameraYVelocity(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYVelocitySignal cameraMovementSignal)
{
	extraState->camera.camera_velocity.y = cameraMovementSignal;
	extraState->camera.camera_acceleration.y = 0;
}

void EVT_decelerateCameraX(
	struct EXS_ExtraState *extraState,
	const EVT_CameraXDecelerateSignal cameraDecelerateSignal)
{
	// predicate to ensuure that the player cant go hyper speeds
	if (SIGN(extraState->camera.camera_velocity.x)
		    + SIGN(cameraDecelerateSignal)
	    == 0) {
		extraState->camera.camera_acceleration.x =
			cameraDecelerateSignal;
	}
}

void EVT_decelerateCameraY(
	struct EXS_ExtraState *extraState,
	const EVT_CameraYDecelerateSignal cameraDecelerateSignal)
{
	if (SIGN(extraState->camera.camera_velocity.y)
		    + SIGN(cameraDecelerateSignal)
	    == 0) {

		extraState->camera.camera_acceleration.y =
			cameraDecelerateSignal;
	}
}
// -----------------------------------------
//    private
// -----------------------------------------
