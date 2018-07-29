#include "EventEffects.h"
#include "../Input/InputHandler.h"
#include "../Components/ComponentsGenerics.h"
#include "../Components/MovementGenerics.h"

// -----------------------------------------
//    private
// -----------------------------------------


// -----------------------------------------
//    public
// -----------------------------------------

#define TEST_RECT_ATTR                                                         \
	CPT_addComponent(components, &(Acceleration){.x = 0, .y = -2});        \
                                                                               \
	CPT_addComponent(components, &(Velocity){.x = 0, .y = -2});            \
                                                                               \
	Position transform = (Position){.x = 50, .y = 50};                     \
	struct V2 tmppp = INP_getScreenMousePosition(                          \
		&extrastate->camera.camera_position);                          \
	Position tmppos = MVT_sub((const Position *)&tmppp, &transform);       \
	CPT_addComponent(components, &tmppos);                                 \
                                                                               \
	CPT_addComponent(                                                      \
		components,                                                    \
		&(Appearance){                                                 \
			.texture =                                             \
				resources->cResources.cTextures.testTexture,   \
			.srcrect =                                             \
				(SDL_Rect){                                    \
					.x = 0, .y = 0, .w = 100, .h = 100},   \
			.dstrect =                                             \
				(SDL_Rect){                                    \
					.x = 0, .y = 0, .w = 100, .h = 100},   \
			.angle = 0});


void EVT_spawnTestARect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	CPT_addComponent(
		components,
		&(ARectAabb){.pMin = *(struct V2 *)&tmppos,
			     .pMax = V2_add((struct V2 *)&tmppos,
					    &(struct V2){.x = 100, .y = 100})});
}

void EVT_spawnTestBRect(struct CPT_Components *components,
			const struct ECS_ResourceRegistry *resources,
			const struct EXS_ExtraState *extrastate)
{

	printf("\n BRECT: \n");
	CPT_updateCurFreeIndex(components);

	TEST_RECT_ATTR

	// adding brectaabb
	CPT_addComponent(
		components,
		&(BRectAabb){.pMin = *(struct V2 *)&tmppos,
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
