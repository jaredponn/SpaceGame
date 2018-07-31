#include "ApplyMovementTransforms.h"
#include "Src/Engine/Components/Movement.h"
#include "SYS_Util.h"

// -----------------------------------------
//    Private function declarations
// -----------------------------------------

// adds the velocity * time to the position
static void SYS_updatePositionWithVelocity(Position *, const Velocity *, Time);

// adds the acceleration * time to the position
static void SYS_updateVelocityWithAcceleration(Velocity *, const Acceleration *,
					       Time);

// -----------------------------------------
//    macros
// -----------------------------------------

#define TRANSFORM_MANAGER_WITH_EXTRA_ARG(                                               \
	transformdata,	/** <..>Manager* ... data to be transformed*/             \
	transformdata_prefix, /** prefix of the transformdata type  for the             \
				 manager and vector. should be the same as the          \
				 type*/                                                 \
	func,		      /** function that follows the format of:                  \
				 FUNC(transformdata_prefix*, constdata_prefix*, arg) */ \
	arg,		      /** third argument to "func"*/                            \
	constdata,	    /** the other data used to transform the data*/           \
	constdata_prefix /**the other data's prefix*/)                                  \
	{                                                                               \
		/** getting the transform data's vector, and itslength*/                \
		const struct transformdata_prefix##Vector                               \
			*transformdata##Data =                                          \
				transformdata_prefix##Manager_get_packed_data(          \
					transformdata);                                 \
		const size_t transformdata##VecLength =                                 \
			transformdata_prefix##Vector_size(                              \
				transformdata##Data);                                   \
                                                                                        \
		/** temporary vars*/                                                    \
		void *transformdata_prefix##Tmp0, *constdata_prefix##Tmp;               \
                                                                                        \
		for (size_t i = 0; i < transformdata##VecLength; ++i) {                 \
			transformdata_prefix##Tmp0 =                                    \
				transformdata_prefix##Vector_get_p(                     \
					transformdata##Data, i);                        \
			constdata_prefix##Tmp = constdata_prefix##Manager_get_p_at(     \
				(struct constdata_prefix##Manager *)constdata,          \
				transformdata_prefix##Manager_get_index_from(           \
					transformdata, i));                             \
			/** checking if that data exists before applying the            \
			 * transform*/                                                  \
			if (transformdata_prefix##Tmp0 != NULL                          \
			    && constdata_prefix##Tmp != NULL)                           \
				func(transformdata_prefix##Tmp0,                        \
				     constdata_prefix##Tmp, arg);                       \
		}                                                                       \
	}
// -----------------------------------------
//    Public function implementations
// -----------------------------------------

void SYS_applyVelocity(const struct V2Manager *const velocityManager,
		       struct V2Manager *const positionManager, const Time dt)
{
	TRANSFORM_MANAGER_WITH_EXTRA_ARG(positionManager, V2,
					 SYS_updatePositionWithVelocity, dt,
					 velocityManager, V2)
}

void SYS_applyAcceleration(const struct V2Manager *const accelerationManager,
			   struct V2Manager *const velocityManager,
			   const Time dt)
{

	TRANSFORM_MANAGER_WITH_EXTRA_ARG(velocityManager, V2,
					 SYS_updateVelocityWithAcceleration, dt,
					 accelerationManager, V2)
}

// -----------------------------------------
//    Private function implementations
// -----------------------------------------


static void SYS_updateVelocityWithAcceleration(Velocity *vel,
					       const Acceleration *acc, Time dt)
{
	*vel = CPT_applyAccelerationToVelocity(acc, vel, dt);
}


static void SYS_updatePositionWithVelocity(Position *pos, const Velocity *vel,
					   Time dt)
{

	*pos = CPT_applyVelocityToPosition(vel, pos, dt);
}
