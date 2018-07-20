#pragma once

#include "Lib/Time.h"
#include "Src/Engine/Components/EngineComponents.h"
#include "Src/Engine/Components/Movement.h"

// applies the velocity to the position to change the positions
void SYS_applyVelocity(const struct Velocity_Manager* const,
                       struct Position_Manager* const, const Time);

// applies the acceleration to the position to change the positions
void SYS_applyAcceleration(const struct Acceleration_Manager* const,
                           struct Velocity_Manager*, const Time);
