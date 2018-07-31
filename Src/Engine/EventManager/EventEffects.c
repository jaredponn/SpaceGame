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

void EVT_updateCameraVelocity(struct EXS_ExtraState *extraState,
			      const EVT_CameraMovementSignal *camVelocitySignal)
{
	extraState->camera.camera_velocity =
		V2_add(&extraState->camera.camera_velocity, camVelocitySignal);
}
// -----------------------------------------
//    private
// -----------------------------------------
