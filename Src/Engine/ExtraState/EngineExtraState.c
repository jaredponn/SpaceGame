#include "stdio.h"
#include "EngineExtraState.h"
#define CAMERA_MOVEMENT_DECAY 5000

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

	engineExtraState->camera.camera_movement_decay = CAMERA_MOVEMENT_DECAY;

	engineExtraState->dt = UTI_zeroTime();
}


void EXS_applyCameraMovement(struct EXS_ExtraState *extraState)
{
	printf("\nx acceleration: %.f\n",
	       extraState->camera.camera_acceleration.x);
	printf("x vel: %.f\n", extraState->camera.camera_velocity.x);
	printf("x pos: %.f\n", extraState->camera.camera_position.x);

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
	if (-15 < cameraVelocity.x && cameraVelocity.x < 15) {
		extraState->camera.camera_acceleration.x = 0;
		extraState->camera.camera_velocity.x = 0;
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
