#include "UpdatePositions.h"
// -----------------------------------------
//    Private function declarations
// -----------------------------------------

// moves an appearance on the screen to a given position
static void SYS_moveAppearanceTo(struct Appearance *, const Position *);
static void SYS_moveRectAabbTo(struct RectAabb *, const Position *);
static void SYS_moveCircAabbTo(struct CircAabb *, const Position *);

// -----------------------------------------
//    Public function implementations
// -----------------------------------------
#define TRANSFORM_MANAGER_WITH(                                                     \
	transformdata,	/** <..>Manager* ... data to be transformed*/         \
	transformdata_prefix, /** prefix of the transformdata type  for the         \
				 manager and vector. should be the same as the      \
				 type*/                                             \
	func,		      /** function that follows the format of:              \
				 FUNC(transformdata_prefix*, constdata_prefix*) */  \
	constdata,	    /** the other data used to transform the data*/       \
	constdata_prefix /**the other data's prefix*/)                              \
	{                                                                           \
		/** getting the transform data's vector, and itslength*/            \
		const struct transformdata_prefix##Vector                           \
			*transformdata##Data =                                      \
				transformdata_prefix##Manager_get_packed_data(      \
					transformdata);                             \
		const size_t transformdata##VecLength =                             \
			transformdata_prefix##Vector_size(                          \
				transformdata##Data);                               \
                                                                                    \
		/** temporary vars*/                                                \
		void *transformdata_prefix##Tmp, *constdata_prefix##Tmp;            \
                                                                                    \
		for (size_t i = 0; i < transformdata##VecLength; ++i) {             \
			transformdata_prefix##Tmp =                                 \
				transformdata_prefix##Vector_get_p(                 \
					transformdata##Data, i);                    \
			constdata_prefix##Tmp = constdata_prefix##Manager_get_p_at( \
				(struct constdata_prefix##Manager *)constdata,      \
				transformdata_prefix##Manager_get_index_from(       \
					transformdata, i));                         \
			/** checking if that data exists before applying the        \
			 * transform*/                                              \
			if (transformdata_prefix##Tmp != NULL                       \
			    && constdata_prefix##Tmp != NULL)                       \
				func(transformdata_prefix##Tmp,                     \
				     constdata_prefix##Tmp);                        \
		}                                                                   \
	}

void SYS_updatePositions(const struct V2Manager *positionManager,
			 struct AppearanceManager *appearanceManager,
			 struct RectAabbManager *arectManager,
			 struct RectAabbManager *brectManager,
			 struct CircAabbManager *aCircManager,
			 struct CircAabbManager *bCircManager)
{
	TRANSFORM_MANAGER_WITH(appearanceManager, Appearance,
			       SYS_moveAppearanceTo, positionManager, V2)

	TRANSFORM_MANAGER_WITH(arectManager, RectAabb, SYS_moveRectAabbTo,
			       positionManager, V2)

	TRANSFORM_MANAGER_WITH(brectManager, RectAabb, SYS_moveRectAabbTo,
			       positionManager, V2)

	TRANSFORM_MANAGER_WITH(aCircManager, CircAabb, SYS_moveCircAabbTo,
			       positionManager, V2)

	TRANSFORM_MANAGER_WITH(bCircManager, CircAabb, SYS_moveCircAabbTo,
			       positionManager, V2)
}

// -----------------------------------------
//    Private function implementations
// -----------------------------------------
static void SYS_moveAppearanceTo(struct Appearance *appearance,
				 const Position *position)
{
	CPT_setSdlRectPosition(&appearance->dstrect, position);
}

static void SYS_moveRectAabbTo(struct RectAabb *aabb, const Position *position)
{
	struct RectAabb tmpaabb = *aabb;
	struct V2 lengths = V2_sub(&tmpaabb.pMax, &tmpaabb.pMin);
	struct V2 nMin = *(struct V2 *)position;

	*aabb = (struct RectAabb){.pMin = nMin,
				  .pMax = V2_add(&lengths, &nMin)};
}

static void SYS_moveCircAabbTo(struct CircAabb *aabb, const Position *position)
{
	float radius = aabb->radius;

	aabb->center.x = position->x + radius;
	aabb->center.y = position->y + radius;
}
