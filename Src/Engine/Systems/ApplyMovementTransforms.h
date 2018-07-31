#pragma once

#include "Lib/Time.h"
#include "Src/Engine/Components/Components.h"
#include "Src/Engine/Components/Movement.h"

// applies the velocity to the position to change the positions
void SYS_applyVelocity(const struct V2Manager *const velocityManager_p,
		       struct V2Manager *const positionManager_p,
		       const Time dt);

// applies the acceleration to the position to change the positions
void SYS_applyAcceleration(const struct V2Manager *const velocityManager_p,
			   struct V2Manager *const positionManager_p,
			   const Time dt);
