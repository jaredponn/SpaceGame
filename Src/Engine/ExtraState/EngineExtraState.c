#include "EngineExtraState.h"

void ECS_initExtraState(struct ECS_ExtraState *engineExtraState) {
        engineExtraState->camera_position = (struct V2){.x = 0, .y = 0};
        engineExtraState->dt = UTI_zeroTime();
}
