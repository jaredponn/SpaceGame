#pragma once
#include "Lib/Macros.h"
#include "Lib/V2Macros.h"
#include "Lib/Time.h"
// -----------------------------------------
//    Macros
// -----------------------------------------

// X macro of the types of V2s we will have
#define LIST_OF_MOVEMENTS                                                      \
	X_MVT(Acceleration)                                                    \
	X_MVT(Velocity)                                                        \
	X_MVT(Position)

// Declaring the acceleration, velocity and position as each of their own V2s
#define X_MVT(name) V2_DECLARE(name)
LIST_OF_MOVEMENTS
#undef X_MVT

// typedefing the V2s to Acceleration, Velocity, Position
#define X_MVT(name) typedef struct name name;
LIST_OF_MOVEMENTS
#undef X_MVT

// applies the velocity to the position
Position CPT_applyVelocityToPosition(const Velocity *, const Position *,
				     const Time);

// applies the velocity to the position
Velocity CPT_applyAccelerationToVelocity(const Acceleration *, const Velocity *,
					 const Time);
