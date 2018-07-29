#include "stdio.h"
#include "EngineExtraState.h"

void ECS_initExtraState(struct EXS_ExtraState *engineExtraState)
{
	engineExtraState->camera.camera_position = (struct V2){.x = 0, .y = 0};
	engineExtraState->camera.camera_velocity = (struct V2){.x = 0, .y = 0};
	engineExtraState->dt = UTI_zeroTime();
}

void EXS_applyCameraVelocity(struct EXS_ExtraState *extraState)
{
	float dt = UTI_castTimeToSecs(extraState->dt);
	struct V2 cameraVelocity = extraState->camera.camera_velocity;
	extraState->camera.camera_position.x += cameraVelocity.x * dt;
	extraState->camera.camera_position.y += cameraVelocity.y * dt;
}
