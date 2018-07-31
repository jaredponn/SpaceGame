#include "AabbHitTest.h"

void SYS_rectAabbHitTest(const struct RectAabbManager *arectmanager,
			 const struct RectAabbManager *brectmanager,
			 struct EventManager *eventmanager)
{
	const struct RectAabbVector *arectvec =
		RectAabbManager_get_packed_data(arectmanager);
	size_t arectvecSize = RectAabbVector_size(arectvec);

	const struct RectAabbVector *brectvec =
		RectAabbManager_get_packed_data(brectmanager);
	size_t brectvecSize = RectAabbVector_size(brectvec);

	for (size_t i = 0; i < arectvecSize; ++i) {
		for (size_t j = 0; j < brectvecSize; ++j) {
			if (CPT_hitTestRectAabb(
				    RectAabbVector_get_p(arectvec, i),
				    RectAabbVector_get_p(brectvec, j)))

			{
				EventManager_push_back(
					eventmanager,
					(Event){.type = EVT_Collision,
						.collision = (EVT_CollisionSignal){
							.a = RectAabbManager_get_index_from(
								arectmanager,
								i),
							.b = RectAabbManager_get_index_from(
								brectmanager,
								j)}});
			}
		}
	}
}
