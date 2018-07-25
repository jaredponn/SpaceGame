#pragma once

#include "Lib/Time.h"
#include "Src/Engine/Components/EngineComponents.h"
#include "Src/Engine/Components/Movement.h"

// applies the velocity to the position to change the positions
void SYS_applyVelocity(const struct VelocityManager* const velocityManager_p,
                       struct PositionManager* const positionManager_p,
                       const Time dt);

// applies the acceleration to the position to change the positions
void SYS_applyAcceleration(
    const struct AccelerationManager* const velocityManager_p,
    struct VelocityManager* const positionManager_p, const Time dt);
