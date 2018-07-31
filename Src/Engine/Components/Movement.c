#include "Movement.h"

Position CPT_applyVelocityToPosition(const Velocity *vel, const Position *pos,
				     const Time time)
{
	return (Position){.x = vel->x * UTI_castTimeToSecs(time) + pos->x,
			  .y = vel->y * UTI_castTimeToSecs(time) + pos->y};
}

// applies the velocity to the position
Velocity CPT_applyAccelerationToVelocity(const Acceleration *acc,
					 const Velocity *vel, const Time time)
{
	return (Velocity){.x = acc->x * UTI_castTimeToSecs(time) + vel->x,
			  .y = acc->y * UTI_castTimeToSecs(time) + vel->y};
}

VECTOR_DEFINE(V2, V2)
COMPONENT_MANAGER_DEFINE(V2, V2, V2)
