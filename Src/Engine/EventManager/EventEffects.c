#include "EventEffects.h"
#include "../Input/InputHandler.h"

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
			.texture =                                             \
				resources->cResources.cTextures.testTexture,   \
			.srcrect =                                             \
				(SDL_Rect){                                    \
					.x = 0, .y = 0, .w = 100, .h = 100},   \
			.dstrect = (SDL_Rect){                                 \
				.x = 0, .y = 0, .w = 100, .h = 100}});


void EVT_spawnTestARect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	CPT_addRectAabb0(
		components,
		&(struct RectAabb){
			.pMin = *(struct V2 *)&tmppos,
			.pMax = V2_add((struct V2 *)&tmppos,
				       &(struct V2){.x = 100, .y = 100})});
}

void EVT_spawnTestBRect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	// adding brectaabb
	CPT_addRectAabb1(
		components,
		&(struct RectAabb){
			.pMin = *(struct V2 *)&tmppos,
			.pMax = V2_add((struct V2 *)&tmppos,
				       &(struct V2){.x = 100, .y = 100})});
}

void EVT_moveCamera(struct EXS_ExtraState *extraState,
		    const EVT_CameraVelocitySignal *cameraMovementSignal)
{
	extraState->camera.camera_velocity = V2_add(
		&extraState->camera.camera_velocity, cameraMovementSignal);
	extraState->camera.camera_acceleration.x = 0;
	extraState->camera.camera_acceleration.y = 0;

	/** const struct V2 halvedV2 = V2_smul(cameraMovementSignal, 0.5); */
	/** extraState->camera.camera_acceleration = */
	/**         V2_add(&extraState->camera.camera_acceleration, &halvedV2);
	 */
}

void EVT_decelerateCamera(
	struct EXS_ExtraState *extraState,
	const EVT_CameraDecelerateSignal *cameraDecelerateSignal)
{
	extraState->camera.camera_acceleration =
		V2_add(&extraState->camera.camera_acceleration,
		       cameraDecelerateSignal);
}
// -----------------------------------------
//    private
// -----------------------------------------
