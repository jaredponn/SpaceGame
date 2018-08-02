#include "AabbHitTest.h"

// TODO find a way to make this stuff more generic so we don't literally copy
// and paste the same thing....

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

void SYS_circAabbHitTest(const struct CircAabbManager *aCircManager,
			 const struct CircAabbManager *bCircManager,
			 struct EventManager *eventManager)
{
	const struct CircAabbVector *arectvec =
		CircAabbManager_get_packed_data(aCircManager);
	size_t arectvecSize = CircAabbVector_size(arectvec);

	const struct CircAabbVector *brectvec =
		CircAabbManager_get_packed_data(bCircManager);
	size_t brectvecSize = CircAabbVector_size(brectvec);

	for (size_t i = 0; i < arectvecSize; ++i) {
		for (size_t j = 0; j < brectvecSize; ++j) {
			if (CPT_hitTestCircAabb(
				    CircAabbVector_get_p(arectvec, i),
				    CircAabbVector_get_p(brectvec, j)))

			{
				EventManager_push_back(
					eventManager,
					(Event){.type = EVT_Collision,
						.collision = (EVT_CollisionSignal){
							.a = CircAabbManager_get_index_from(
								aCircManager,
								i),
							.b = CircAabbManager_get_index_from(
								bCircManager,
								j)}});
			}
		}
	}
}
