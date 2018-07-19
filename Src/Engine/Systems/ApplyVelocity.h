#pragma once

#include "Lib/Time.h"
#include "Src/Engine/Components/Position.h"
#include "Src/Engine/Components/Velocity.h"

// applies the velocity to the position to change the positions
void SYS_applyVelocity(const struct Velocity_Manager* const,
                       struct Position_Manager* const, const Time);
