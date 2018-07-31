#pragma once
#include "Lib/V2.h"
#include "Lib/GenericComponentManager.h"
#include "Lib/GenericVector.h"
#include "Lib/Time.h"
// -----------------------------------------
//    Macros
// -----------------------------------------

typedef struct V2 Velocity;
typedef struct V2 Position;
typedef struct V2 Acceleration;


// applies the velocity to the position
Position CPT_applyVelocityToPosition(const Velocity *, const Position *,
				     const Time);

// applies the velocity to the position
Velocity CPT_applyAccelerationToVelocity(const Acceleration *, const Velocity *,
					 const Time);


VECTOR_DECLARE(struct V2, V2)
COMPONENT_MANAGER_DECLARE(struct V2, V2, V2)
