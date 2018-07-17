#pragma once

#include "Src/Engine/Components/Acceleration.h"
#include "Src/Engine/Components/Velocity.h"
#include "Src/Engine/Core/Time.h"

// applies the acceleration to the position to change the positions
void SYS_applyAcceleration(const struct Acceleration_Manager* const,
                           struct Velocity_Manager*, const Time);
