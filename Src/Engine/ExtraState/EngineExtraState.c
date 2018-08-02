#include "EngineExtraState.h"
#include "../GameConfig.h"

// -----------------------------------------
//    private funcs
// -----------------------------------------

static inline void EXS_stopDeceleration(struct EXS_ExtraState *);
static inline void EXS_applyCameraAcceleration(struct EXS_ExtraState *);
static inline void EXS_applyCameraVelocity(struct EXS_ExtraState *);

// -----------------------------------------
//    pubic
// -----------------------------------------


void ECS_initExtraState(struct EXS_ExtraState *engineExtraState)
{
	engineExtraState->camera.camera_acceleration =
		(struct V2){.x = 0, .y = 0};
	engineExtraState->camera.camera_position = (struct V2){.x = 0, .y = 0};
	engineExtraState->camera.camera_velocity = (struct V2){.x = 0, .y = 0};

	engineExtraState->dt = UTI_zeroTime();
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
