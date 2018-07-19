#pragma once

#include "Lib/Time.h"
#include "Src/Engine/Components/Acceleration.h"
#include "Src/Engine/Components/Velocity.h"

// applies the acceleration to the position to change the positions
void SYS_applyAcceleration(const struct Acceleration_Manager* const,
                           struct Velocity_Manager*, const Time);
