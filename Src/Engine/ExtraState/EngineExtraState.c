#include "EngineExtraState.h"
#include "../GameConfig.h"
#include <string.h>

#define INIT_FOCUSED_BUFFER_SIZE 100

// -----------------------------------------
//    private funcs
// -----------------------------------------

static inline void EXS_stopDeceleration(struct EXS_ExtraState *);
static inline void EXS_applyCameraAcceleration(struct EXS_ExtraState *);
static inline void EXS_applyCameraVelocity(struct EXS_ExtraState *);

// -----------------------------------------
//    pubic
// -----------------------------------------


void ECS_initExtraState(struct EXS_ExtraState *extraState)
{
	memset(extraState, 0, sizeof(struct EXS_ExtraState));
	SizetVector_init(&extraState->focused_entities);
	SizetVector_reserve(&extraState->focused_entities,
			    INIT_FOCUSED_BUFFER_SIZE);
}


void EXS_applyCameraMovement(struct EXS_ExtraState *extraState)
{
	EXS_applyCameraAcceleration(extraState);
	EXS_applyCameraVelocity(extraState);

	EXS_stopDeceleration(extraState);
}
// -----------------------------------------
//    private funcs
// -----------------------------------------

static inline void EXS_stopDeceleration(struct EXS_ExtraState *extraState)
{
	struct V2 cameraVelocity = extraState->camera.camera_velocity;
	if (-DECELERATE_RANGE < cameraVelocity.x
	    && cameraVelocity.x < DECELERATE_RANGE) {
		extraState->camera.camera_acceleration.x = 0;
		extraState->camera.camera_velocity.x = 0;
	}

	if (-DECELERATE_RANGE < cameraVelocity.y
	    && cameraVelocity.y < DECELERATE_RANGE) {
		extraState->camera.camera_acceleration.y = 0;
		extraState->camera.camera_velocity.y = 0;
	}
}

static inline void
EXS_applyCameraAcceleration(struct EXS_ExtraState *extraState)
{
	float dt = UTI_castTimeToSecs(extraState->dt);
	struct V2 cameraAcceleration = extraState->camera.camera_acceleration;

	extraState->camera.camera_velocity.x += cameraAcceleration.x * dt;
	extraState->camera.camera_velocity.y += cameraAcceleration.y * dt;
}
static inline void EXS_applyCameraVelocity(struct EXS_ExtraState *extraState)
{

	float dt = UTI_castTimeToSecs(extraState->dt);
	struct V2 cameraVelocity = extraState->camera.camera_velocity;

	extraState->camera.camera_position.x += cameraVelocity.x * dt;
	extraState->camera.camera_position.y += cameraVelocity.y * dt;
}
